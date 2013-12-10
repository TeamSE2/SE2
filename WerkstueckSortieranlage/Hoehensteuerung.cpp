
#include "Hoehensteuerung.h"


namespace PetriNetzBandEins{

Hoehensteuerung *Hoehensteuerung::instance = NULL;

Hoehensteuerung::Hoehensteuerung(){
	initNetz();
	Dispatcher::getInstance()->anmelden(this, LICHTSCHRANKE_HOEHENMESSUNG, P_B);
	Dispatcher::getInstance()->anmelden(this, HOEHENMESSUNG_CHECK, P_B);
}

Hoehensteuerung::~Hoehensteuerung(){
	Dispatcher::getInstance()->abmelden(this, LICHTSCHRANKE_HOEHENMESSUNG, P_B);
	Dispatcher::getInstance()->abmelden(this, HOEHENMESSUNG_CHECK, P_B);

	delete instance;
	instance = NULL;
}

Hoehensteuerung* Hoehensteuerung::getInstance(){
	if(instance == NULL){
		instance = new Hoehensteuerung();
	}

	return instance;
}

void Hoehensteuerung::initNetz(){
	plaetze[GZ] = 1;
	plaetze[CHECK_T] = 0;
	plaetze[CHECK_L_1] = 0;
	plaetze[CHECK_L_2] = 0;
	eingang[LICHTSCHRANKE] = 1;
	eingang[HOEHE] = 0;
}

void Hoehensteuerung::ladeWerkstueck(){
 temp_ws = SynBandEins::getInstance()->popWerkstueckHoehenmessung();
}

void Hoehensteuerung::sendeWerkstueck(){
	SynBandEins::getInstance()->pushWerkstueckWeiche(temp_ws);
	SynBandEins::getInstance()->pushWerkstueckDetektor(temp_ws);
}

void Hoehensteuerung::aktualisiereSignale(uint8_t iq, uint8_t state){

	switch (iq) {
		case LICHTSCHRANKE_HOEHENMESSUNG:
//			cout << "lichtschranke: "<< endl;
//			printf("%i",state);
			eingang[LICHTSCHRANKE] = state;
			break;
		case HOEHENMESSUNG_CHECK:
			eingang[HOEHE] = state;
		default:
			break;
	}
}

void Hoehensteuerung::schreibeSignale(){

	if(plaetze[CHECK_L_2]){
		if(checkLoch()){
			eingang[LOCH_H] = 1;
			(*temp_ws).typ = BOHRUNG_OBEN;
		}else{
			eingang[LOCH_H] = 0;
			(*temp_ws).typ = BOHRUNG_UNTEN;
		}

		// todo: lese und speicher hoehenwert.
	}

	if(plaetze[CHECK_T] || plaetze[CHECK_L_1] || plaetze[CHECK_L_2]){
		HAL::getInstance().getMotor()->langsam(true);
	}else{
		HAL::getInstance().getMotor()->langsam(false);
	}

}

void Hoehensteuerung::transitionenAusfuehren(){
	if (plaetze[GZ] && !plaetze[CHECK_T] && !eingang[LICHTSCHRANKE]) {
		printf("1.1:  GZ: %i, CHECK_T: %i, CHECK_L_1: %i, CHECK_L_2: %i,   \n",plaetze[GZ], plaetze[CHECK_T], plaetze[CHECK_L_1], plaetze[CHECK_L_2]);
		plaetze[GZ] = 0;
		plaetze[CHECK_T] = 1;
		printf("1.2:  GZ: %i, CHECK_T: %i, CHECK_L_1: %i, CHECK_L_2: %i,   \n",plaetze[GZ], plaetze[CHECK_T], plaetze[CHECK_L_1], plaetze[CHECK_L_2]);
		printf("LS: %i, H: %i\n",eingang[LICHTSCHRANKE], eingang[HOEHE]);
		ladeWerkstueck();
	}

//	if (plaetze[CHECK_T] && !plaetze[GZ] && eingang[LICHTSCHRANKE]) {
//		plaetze[CHECK_T] = 0;
//		plaetze[GZ] = 1;
//		printf("2:  GZ: %i, CHECK_T: %i, CHECK_L_1: %i, CHECK_L_2: %i,   \n",plaetze[GZ], plaetze[CHECK_T], plaetze[CHECK_L_1], plaetze[CHECK_L_2]);
//		sendeWerkstueck();
//	}

//	if(plaetze[CHECK_L_2] && !plaetze[CHECK_L_1] && !eingang[HOEHE] && !eingang[LOCH_H]){
//		plaetze[CHECK_L_2] = 0;
//		plaetze[CHECK_L_1] = 1;
//		printf("4:  GZ: %i, CHECK_T: %i, CHECK_L_1: %i, CHECK_L_2: %i,   \n",plaetze[GZ], plaetze[CHECK_T], plaetze[CHECK_L_1], plaetze[CHECK_L_2]);
//	}

	if (plaetze[CHECK_T] && !plaetze[CHECK_L_2] && eingang[HOEHE]) {
		plaetze[CHECK_T] = 0;
		plaetze[CHECK_L_2] = 1;
		printf("3:  GZ: %i, CHECK_T: %i, CHECK_L_1: %i, CHECK_L_2: %i,   \n",plaetze[GZ], plaetze[CHECK_T], plaetze[CHECK_L_1], plaetze[CHECK_L_2]);
		printf("LS: %i, H: %i\n",eingang[LICHTSCHRANKE], eingang[HOEHE]);
	}

	if (plaetze[CHECK_T] && !plaetze[CHECK_L_1] && !eingang[HOEHE]) {
		plaetze[CHECK_T] = 0;
		plaetze[CHECK_L_1] = 1;
		printf("4:  GZ: %i, CHECK_T: %i, CHECK_L_1: %i, CHECK_L_2: %i,   \n",plaetze[GZ], plaetze[CHECK_T], plaetze[CHECK_L_1], plaetze[CHECK_L_2]);
		printf("LS: %i, H: %i\n",eingang[LICHTSCHRANKE], eingang[HOEHE]);
	}

	if(plaetze[CHECK_L_1] && !plaetze[CHECK_L_2] && eingang[HOEHE]){
		plaetze[CHECK_L_1] = 0;
		plaetze[CHECK_L_2] = 1;
		printf("5:  GZ: %i, CHECK_T: %i, CHECK_L_1: %i, CHECK_L_2: %i,   \n",plaetze[GZ], plaetze[CHECK_T], plaetze[CHECK_L_1], plaetze[CHECK_L_2]);
		printf("LS: %i, H: %i\n",eingang[LICHTSCHRANKE], eingang[HOEHE]);
	}

	if (plaetze[CHECK_L_1] && !plaetze[GZ] && eingang[LICHTSCHRANKE]) {
		plaetze[CHECK_L_1] = 0;
		plaetze[GZ] = 1;
		printf("6:  GZ: %i, CHECK_T: %i, CHECK_L_1: %i, CHECK_L_2: %i,   \n",plaetze[GZ], plaetze[CHECK_T], plaetze[CHECK_L_1], plaetze[CHECK_L_2]);
		sendeWerkstueck();
		printf("LS: %i, H: %i\n",eingang[LICHTSCHRANKE], eingang[HOEHE]);
	}

	if (plaetze[CHECK_L_2] && !plaetze[GZ] && eingang[LICHTSCHRANKE]) {
		plaetze[CHECK_L_2] = 0;
		plaetze[GZ] = 1;
		printf("7:  GZ: %i, CHECK_T: %i, CHECK_L_1: %i, CHECK_L_2: %i,   \n",plaetze[GZ], plaetze[CHECK_T], plaetze[CHECK_L_1], plaetze[CHECK_L_2]);
		sendeWerkstueck();
		printf("LS: %i, H: %i\n",eingang[LICHTSCHRANKE], eingang[HOEHE]);
	}
}

void Hoehensteuerung::execute(){
	transitionenAusfuehren();
	schreibeSignale();
}

bool Hoehensteuerung::checkLoch(){
	return true;
}

}
