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
	plaetze[LESE] = 0;
	plaetze[WARTE_U] = 0;
	eingang[LICHTSCHRANKE] = 1;
}

void Uebergabesteuerung::ladeWerkstueck(){

	temp_ws = SynBandEins::getInstance()->popWerkstueckUebergabe();
}

bool Uebergabesteuerung::aktualisiereSignale(uint8_t port, uint8_t iq, uint8_t state){
	bool execute = false;

 	 if(port == P_B){
 		 if(iq == LICHTSCHRANKE_AUSLAUF){
 			 eingang[LICHTSCHRANKE] = state;
 			 execute = true;
 		 }
 	 }

 	 if(port == SYN_BAND_EINS){
 		 switch (iq) {
			case UEBERGABE_ENDE:
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

	if(plaetze[LESE]){
		SynBandEins::getInstance()->setMotorStop();
	}

}

void Uebergabesteuerung::transitionenAusfuehren(){

	if(plaetze[GZ] && !plaetze[LESE] && !eingang[LICHTSCHRANKE]){
		plaetze[GZ] = 0;
		plaetze[LESE] = 1;
		ladeWerkstueck();
		SerielleSchnittstelle::getInstance().sendeNachricht(WERKSTUECK);
		printf("\nUebergabe: 1:  GZ: %i, LESE: %i, WARTE_U: %i\n",plaetze[GZ], plaetze[LESE], plaetze[WARTE_U]);

	}

	if (plaetze[LESE] && !plaetze[WARTE_U] && SynBandEins::getInstance()->getSynUebergabeBereit()) {
		SerielleSchnittstelle::getInstance().sendeWerkstueckDaten(temp_ws);
		SynBandEins::getInstance()->dekrementSynUebergabeBereit();
		plaetze[LESE] = 0;
		plaetze[WARTE_U] = 1;
		SynBandEins::getInstance()->inkrementSynUebergabeStart();
		printf("\nUebergabe: 2:  GZ: %i, LESE: %i, WARTE_U: %i\n",plaetze[GZ], plaetze[LESE], plaetze[WARTE_U]);
	}

	if (plaetze[WARTE_U] && !plaetze[GZ] && SynBandEins::getInstance()->getSynUebergabeEnde()) {
		plaetze[WARTE_U] = 0;
		SynBandEins::getInstance()->dekrementSynUebergabeEnde();

		plaetze[GZ] = 1;
		printf("\nUebergabe: 3:  GZ: %i, LESE: %i, WARTE_U: %i\n",plaetze[GZ], plaetze[LESE], plaetze[WARTE_U]);
	}
}

void Uebergabesteuerung::execute(){
	transitionenAusfuehren();
	schreibeSignale();
}

}
