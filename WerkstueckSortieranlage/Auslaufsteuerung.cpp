#include "Auslaufsteuerung.h"


namespace PetriNetzBandEins {

Auslaufsteuerung *Auslaufsteuerung::instance = NULL;

Auslaufsteuerung::Auslaufsteuerung(){
	initNetz();
	Dispatcher::getInstance()->anmelden(this);
}

Auslaufsteuerung::~Auslaufsteuerung(){
	Dispatcher::getInstance()->abmelden(this);
	delete instance;
	instance = NULL;
}

Auslaufsteuerung* Auslaufsteuerung::getInstance(){
	if(instance == NULL){
		instance = new Auslaufsteuerung();
	}

	return instance;
}

void Auslaufsteuerung::initNetz(){
	plaetze[GZ] = 1;
	plaetze[CHECK_1] = 0;
	plaetze[CHECK_2] = 0;
	plaetze[WENDEN_1] = 0;
	plaetze[WENDEN_2] = 0;
	plaetze[UEBERGABE] = 0;
	plaetze[WARTE_A] = 0;
	eingang[LICHTSCHRANKE_A] = 1;
	eingang[LOCH] = 0;
	eingang[METALL_A] = 0;
}

void Auslaufsteuerung::ladeWerkstueck(){
	temp_ws = SynBandEins::getInstance()->popWerkstueckAuslauf();

	if ((*temp_ws).typ == BOHRUNG_OBEN || (*temp_ws).typ == BOHRUNG_OBEN_METALL ) {
		eingang[LOCH] = 1;
	}else{
		eingang[LOCH] = 0;
	}

	if ((*temp_ws).typ == BOHRUNG_UNTEN_METALL || (*temp_ws).typ == BOHRUNG_OBEN_METALL ) {
		eingang[METALL_A] = 1;
	}else{
		eingang[METALL_A] = 0;
	}

		printf("Werkstueck ID: %i \n"
				"Metall: %i\n"
				"Loch: %i\n"
				, (*temp_ws).id, eingang[METALL_A], eingang[LOCH]);
}

bool Auslaufsteuerung::aktualisiereSignale(uint8_t port, uint8_t iq, uint8_t state){
 bool execute = false;

 	 if(port == P_B){
 		 if(iq == LICHTSCHRANKE_AUSLAUF){
 			 eingang[LICHTSCHRANKE_A] = state;
 			 execute = true;
 		 }
 	 }

 	 if(port == SYN_BAND_EINS){
 		 if(iq == UEBERGABE_START){
 			 execute = true;
 		 }
 	 }

	 return execute;
}

void Auslaufsteuerung::schreibeSignale(){

	if(plaetze[WENDEN_1] || plaetze[WENDEN_2] || plaetze[UEBERGABE]){
		SynBandEins::getInstance()->setMotorStop();
		//stop Timer
	}
	if(plaetze[WENDEN_1] || plaetze[WENDEN_2]){

//		HAL::getInstance().getAmpel()->gelbBlinken(1000);
//		SynBandEins::getInstance()->setAmpelGruenAus();
	}else{
//		HAL::getInstance().getAmpel()->gelb(false);
	}


}

void Auslaufsteuerung::transitionenAusfuehren(){

	if(plaetze[GZ] && !plaetze[CHECK_1] && !eingang[LICHTSCHRANKE_A]){
		plaetze[GZ] = 0;
		plaetze[CHECK_1] = 1;
		ladeWerkstueck();

		printf("1:  GZ: %i,CHECK_1: %i, CHECK_2: %i, WENDEN_1: %i, WENDEN_2: %i, UEBERGABE: %i, WARTE_A: %i\n"
							,plaetze[GZ], plaetze[CHECK_1], plaetze[CHECK_2], plaetze[WENDEN_1], plaetze[WENDEN_2], plaetze[UEBERGABE], plaetze[WARTE_A]);

	}


	if(plaetze[CHECK_1] && !plaetze[CHECK_2] && eingang[LOCH]){
		plaetze[CHECK_1] = 0;
		plaetze[CHECK_2] = 1;
		printf("2:  GZ: %i,CHECK_1: %i, CHECK_2: %i, WENDEN_1: %i, WENDEN_2: %i, UEBERGABE: %i, WARTE_A: %i\n"
							,plaetze[GZ], plaetze[CHECK_1], plaetze[CHECK_2], plaetze[WENDEN_1], plaetze[WENDEN_2], plaetze[UEBERGABE], plaetze[WARTE_A]);

	}

	if(plaetze[CHECK_1] && !plaetze[WENDEN_1] && !eingang[LOCH]){
		plaetze[CHECK_1] = 0;
		plaetze[WENDEN_1] = 1;
		printf("3:  GZ: %i,CHECK_1: %i, CHECK_2: %i, WENDEN_1: %i, WENDEN_2: %i, UEBERGABE: %i, WARTE_A: %i\n"
							,plaetze[GZ], plaetze[CHECK_1], plaetze[CHECK_2], plaetze[WENDEN_1], plaetze[WENDEN_2], plaetze[UEBERGABE], plaetze[WARTE_A]);
	}

	if(plaetze[CHECK_2] && !plaetze[WENDEN_1] && eingang[METALL_A]){
		plaetze[CHECK_2] = 0;
		plaetze[WENDEN_1] = 1;
		printf("4:  GZ: %i,CHECK_1: %i, CHECK_2: %i, WENDEN_1: %i, WENDEN_2: %i, UEBERGABE: %i, WARTE_A: %i\n"
							,plaetze[GZ], plaetze[CHECK_1], plaetze[CHECK_2], plaetze[WENDEN_1], plaetze[WENDEN_2], plaetze[UEBERGABE], plaetze[WARTE_A]);
	}

	if(plaetze[CHECK_2] && !plaetze[UEBERGABE] && !eingang[METALL_A]){
		plaetze[CHECK_2] = 0;
		plaetze[UEBERGABE] = 1;
		printf("5:  GZ: %i,CHECK_1: %i, CHECK_2: %i, WENDEN_1: %i, WENDEN_2: %i, UEBERGABE: %i, WARTE_A: %i\n"
							,plaetze[GZ], plaetze[CHECK_1], plaetze[CHECK_2], plaetze[WENDEN_1], plaetze[WENDEN_2], plaetze[UEBERGABE], plaetze[WARTE_A]);
	}

	if(plaetze[WENDEN_1] && !plaetze[WENDEN_2] && eingang[LICHTSCHRANKE_A]){
		plaetze[WENDEN_1] = 0;
		plaetze[WENDEN_2] = 1;
		printf("6:  GZ: %i,CHECK_1: %i, CHECK_2: %i, WENDEN_1: %i, WENDEN_2: %i, UEBERGABE: %i, WARTE_A: %i\n"
							,plaetze[GZ], plaetze[CHECK_1], plaetze[CHECK_2], plaetze[WENDEN_1], plaetze[WENDEN_2], plaetze[UEBERGABE], plaetze[WARTE_A]);
	}

	if(plaetze[WENDEN_2] && !plaetze[UEBERGABE] && !eingang[LICHTSCHRANKE_A]){
		plaetze[WENDEN_2] = 0;
		plaetze[UEBERGABE] = 1;
		printf("7:  GZ: %i,CHECK_1: %i, CHECK_2: %i, WENDEN_1: %i, WENDEN_2: %i, UEBERGABE: %i, WARTE_A: %i\n"
							,plaetze[GZ], plaetze[CHECK_1], plaetze[CHECK_2], plaetze[WENDEN_1], plaetze[WENDEN_2], plaetze[UEBERGABE], plaetze[WARTE_A]);
	}

	if(plaetze[UEBERGABE] && !plaetze[WARTE_A] && SynBandEins::getInstance()->getSynUebergabeStart()){
		SynBandEins::getInstance()->dekrementSynUebergabeStart();
		plaetze[UEBERGABE] = 0;
		plaetze[WARTE_A] = 1;
		printf("8:  GZ: %i,CHECK_1: %i, CHECK_2: %i, WENDEN_1: %i, WENDEN_2: %i, UEBERGABE: %i, WARTE_A: %i\n"
							,plaetze[GZ], plaetze[CHECK_1], plaetze[CHECK_2], plaetze[WENDEN_1], plaetze[WENDEN_2], plaetze[UEBERGABE], plaetze[WARTE_A]);
	}

	//todo: hier warten bis Werkstueck Band verlassen hat.
	if(plaetze[WARTE_A] && !plaetze[GZ]){
		SynBandEins::getInstance()->inkrementSynUebergabeEnde();
		SynBandEins::getInstance()->inkrementSynVerlassen();
		plaetze[WARTE_A] = 0;
		plaetze[GZ] = 1;
		printf("9:  GZ: %i,CHECK_1: %i, CHECK_2: %i, WENDEN_1: %i, WENDEN_2: %i, UEBERGABE: %i, WARTE_A: %i\n"
							,plaetze[GZ], plaetze[CHECK_1], plaetze[CHECK_2], plaetze[WENDEN_1], plaetze[WENDEN_2], plaetze[UEBERGABE], plaetze[WARTE_A]);
	}

}

void Auslaufsteuerung::execute(){
	transitionenAusfuehren();
	schreibeSignale();
}


}
