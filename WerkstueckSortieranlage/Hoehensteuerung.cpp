
#include "Hoehensteuerung.h"


namespace PetriNetzBandEins{

Hoehensteuerung *Hoehensteuerung::instance = NULL;

Hoehensteuerung::Hoehensteuerung(){
	initNetz();
	Dispatcher::getInstance()->anmelden(this);
}

Hoehensteuerung::~Hoehensteuerung(){
	Dispatcher::getInstance()->abmelden(this);

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
	eingang[LOCH_H] = 0;
}

void Hoehensteuerung::ladeWerkstueck(){
	eingang[LOCH_H] = 0;
	temp_ws = SynBandEins::getInstance()->popWerkstueckHoehenmessung();
	cout << temp_ws << endl;
}

void Hoehensteuerung::sendeWerkstueck(){
	SynBandEins::getInstance()->pushWerkstueckWeiche(temp_ws);
	SynBandEins::getInstance()->pushWerkstueckDetektor(temp_ws);
}

bool Hoehensteuerung::aktualisiereSignale(uint8_t port, uint8_t iq, uint8_t state){
	bool execute = false;

	if(port == P_B){
		switch (iq) {
				case LICHTSCHRANKE_HOEHENMESSUNG:
					eingang[LICHTSCHRANKE] = state;
					execute = true;
					break;
				case HOEHENMESSUNG_CHECK:
					eingang[HOEHE] = state;
					execute = true;
				default:
					break;
			}
	}

	return execute;
}

void Hoehensteuerung::schreibeSignale(){

	if(plaetze[CHECK_L_1] && !eingang[LOCH_H]){
		if(checkLoch()){
			eingang[LOCH_H] = 1;

		}else{
			eingang[LOCH_H] = 0;

		}

		// todo: lese und speicher hoehenwert.
	}

	if(plaetze[CHECK_L_2]){
		if(eingang[LOCH_H]){
			(*temp_ws).typ = BOHRUNG_OBEN;
		}else{
			(*temp_ws).typ = BOHRUNG_UNTEN;
		}
	}

	if(plaetze[CHECK_T] || plaetze[CHECK_L_1] || plaetze[CHECK_L_2]){
		HAL::getInstance().getMotor()->langsam(true);
	}else{
		HAL::getInstance().getMotor()->langsam(false);
	}

}

void Hoehensteuerung::transitionenAusfuehren(){
	if (plaetze[GZ] && !plaetze[CHECK_T] && !eingang[LICHTSCHRANKE]) {
		plaetze[GZ] = 0;
		plaetze[CHECK_T] = 1;
		printf("Hoehenmessung : 1:  GZ: %i, CHECK_T: %i, CHECK_L_1: %i, CHECK_L_2: %i,   \n",plaetze[GZ], plaetze[CHECK_T], plaetze[CHECK_L_1], plaetze[CHECK_L_2]);
		ladeWerkstueck();
	}

	if (plaetze[CHECK_T] && !plaetze[CHECK_L_2] && eingang[HOEHE]) {
		plaetze[CHECK_T] = 0;
		plaetze[CHECK_L_2] = 1;
		printf("Hoehenmessung : 2:  GZ: %i, CHECK_T: %i, CHECK_L_1: %i, CHECK_L_2: %i,   \n",plaetze[GZ], plaetze[CHECK_T], plaetze[CHECK_L_1], plaetze[CHECK_L_2]);
		printf("LS: %i, H: %i\n",eingang[LICHTSCHRANKE], eingang[HOEHE]);
	}

	if (plaetze[CHECK_T] && !plaetze[CHECK_L_1] && !eingang[HOEHE]) {
		plaetze[CHECK_T] = 0;
		plaetze[CHECK_L_1] = 1;
		printf("Hoehenmessung : 3:  GZ: %i, CHECK_T: %i, CHECK_L_1: %i, CHECK_L_2: %i,   \n",plaetze[GZ], plaetze[CHECK_T], plaetze[CHECK_L_1], plaetze[CHECK_L_2]);
		printf("LS: %i, H: %i\n",eingang[LICHTSCHRANKE], eingang[HOEHE]);
	}

	if(plaetze[CHECK_L_1] && !plaetze[CHECK_L_2] && eingang[HOEHE]){
		plaetze[CHECK_L_1] = 0;
		plaetze[CHECK_L_2] = 1;
		printf("Hoehenmessung : 4:  GZ: %i, CHECK_T: %i, CHECK_L_1: %i, CHECK_L_2: %i,   \n",plaetze[GZ], plaetze[CHECK_T], plaetze[CHECK_L_1], plaetze[CHECK_L_2]);
		printf("LS: %i, H: %i\n",eingang[LICHTSCHRANKE], eingang[HOEHE]);
	}

	if (plaetze[CHECK_L_1] && !plaetze[GZ] && eingang[LICHTSCHRANKE]) {
		plaetze[CHECK_L_1] = 0;
		plaetze[GZ] = 1;
		sendeWerkstueck();
		printf("Hoehenmessung : 5:  GZ: %i, CHECK_T: %i, CHECK_L_1: %i, CHECK_L_2: %i,   \n",plaetze[GZ], plaetze[CHECK_T], plaetze[CHECK_L_1], plaetze[CHECK_L_2]);
		printf("LS: %i, H: %i\n",eingang[LICHTSCHRANKE], eingang[HOEHE]);
	}

	if (plaetze[CHECK_L_2] && !plaetze[GZ] && eingang[LICHTSCHRANKE]) {
		plaetze[CHECK_L_2] = 0;
		plaetze[GZ] = 1;
		printf("Hoehenmessung : 6:  GZ: %i, CHECK_T: %i, CHECK_L_1: %i, CHECK_L_2: %i,   \n",plaetze[GZ], plaetze[CHECK_T], plaetze[CHECK_L_1], plaetze[CHECK_L_2]);
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
