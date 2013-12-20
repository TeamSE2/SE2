#include "Uebergabesteuerung.h"

namespace PetriNetzBandEins {


Uebergabesteuerung *Uebergabesteuerung::instance = NULL;

Uebergabesteuerung::Uebergabesteuerung(){
	initNetz();
	Dispatcher::getInstance()->anmelden(this);}

Uebergabesteuerung::~Uebergabesteuerung(){
	Dispatcher::getInstance()->abmelden(this);
	delete instance;
	instance = NULL;
}

Uebergabesteuerung* Uebergabesteuerung::getInstance(){
	if(instance == NULL){
		instance = new Uebergabesteuerung();
	}

	return instance;
}

void Uebergabesteuerung::initNetz(){
	plaetze[GZ] = 1;
	plaetze[SENDE_1] = 0;
	plaetze[SENDE_2] = 0;
	plaetze[WARTE_U] = 0;
	eingang[LICHTSCHRANKE] = 1;
}

void Uebergabesteuerung::ladeWerkstueck(){

	temp_ws = SynBandEins::getInstance()->popWerkstueckUebergabe();
}

bool Uebergabesteuerung::aktualisiereSignale(uint8_t port, uint8_t iq, uint8_t state){
	bool execute = false;

 	 if(port == P_B){
 		 if(iq == LICHTSCHRANKE_WEICHE){
 			 eingang[LICHTSCHRANKE] = state;
 			 execute = true;
 		 }
 	 }

 	 if(port == SYN_BAND_EINS){
 		 switch (iq) {
			case UEBERGABE_START:
				execute = true;
				break;
			case UEBERGABE_BEREIT:
				execute = true;
				break;
			default:
				break;
		}
 	 }

 	 return execute;
}

void Uebergabesteuerung::schreibeSignale(){

//	if(plaetze[SENDE_1] || plaetze[SENDE_2]){
//		SynBandEins::getInstance()->setMotorStop();
//	}

}

void Uebergabesteuerung::transitionenAusfuehren(){

		if(plaetze[GZ] && !plaetze[SENDE_1] && SynBandEins::getInstance()->getSynUebergabeStart()){
			ladeWerkstueck();
			if(temp_ws != NULL){
				plaetze[GZ] = 0;
				plaetze[SENDE_1] = 1;
				SynBandEins::getInstance()->dekrementSynUebergabeStart();
				SerielleSchnittstelle::getInstance().sendeNachricht(WERKSTUECK);
			}

			printf("Uebergabe: 1:  GZ: %i, SENDE_1: %i, SENDE_2: %i, WARTE_U: %i\n",plaetze[GZ], plaetze[SENDE_1], plaetze[SENDE_2], plaetze[WARTE_U]);
		}

	if(temp_ws != NULL){
		if(plaetze[SENDE_1] && !plaetze[SENDE_2] && SynBandEins::getInstance()->getSynUebergabeBereit()){
			SynBandEins::getInstance()->dekrementSynUebergabeBereit();
			plaetze[SENDE_1] = 0;
			plaetze[SENDE_2] = 1;
			SerielleSchnittstelle::getInstance().sendeWerkstueckDaten(temp_ws);
			printf("Uebergabe: 2:  GZ: %i, SENDE_1: %i, SENDE_2: %i, WARTE_U: %i\n",plaetze[GZ], plaetze[SENDE_1], plaetze[SENDE_2], plaetze[WARTE_U]);
		}

		if (plaetze[SENDE_2] && !plaetze[GZ] && SynBandEins::getInstance()->getSynUebergabeBereit()) {
			SynBandEins::getInstance()->dekrementSynUebergabeBereit();
			plaetze[SENDE_2] = 0;
			plaetze[GZ] = 1;
			SynBandEins::getInstance()->inkrementSynUebergabeEnde();
			temp_ws = NULL;
			printf("Uebergabe: 3:  GZ: %i, SENDE_1: %i, SENDE_2: %i, WARTE_U: %i\n",plaetze[GZ], plaetze[SENDE_1], plaetze[SENDE_2], plaetze[WARTE_U]);
		}

//		if (plaetze[WARTE_U] && !plaetze[GZ] && SynBandEins::getInstance()->getSynUebergabeEnde()) {
//			plaetze[WARTE_U] = 0;
//			SynBandEins::getInstance()->dekrementSynUebergabeEnde();
//			plaetze[GZ] = 1;
//			printf("Uebergabe: 4:  GZ: %i, SENDE_1: %i, SENDE_2: %i, WARTE_U: %i\n",plaetze[GZ], plaetze[SENDE_1], plaetze[SENDE_2], plaetze[WARTE_U]);
//
//		}
	}
}

void Uebergabesteuerung::execute(){
	transitionenAusfuehren();
	schreibeSignale();
}

}
