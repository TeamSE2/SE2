#include "Uebergabesteuerung.h"

namespace PetriNetzBandEins {


Uebergabesteuerung *Uebergabesteuerung::instance = NULL;

Uebergabesteuerung::Uebergabesteuerung(){
	Dispatcher::getInstance()->anmelden(this, LICHTSCHRANKE_AUSLAUF, P_B);
}

Uebergabesteuerung::~Uebergabesteuerung(){
	Dispatcher::getInstance()->abmelden(this, LICHTSCHRANKE_AUSLAUF, P_B);

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
}

void Uebergabesteuerung::ladeWerkstueck(){

	temp_ws = SynBandEins::getInstance()->popWerkstueckUebergabe();
}

void Uebergabesteuerung::aktualisiereSignale(uint8_t iq, uint8_t state){

	 if(iq == LICHTSCHRANKE_EINLAUF){
		 eingang[LICHTSCHRANKE] = state;
	 }
}

void Uebergabesteuerung::schreibeSignale(){

	if (plaetze[WARTE_U]) {
		//Timer start
	}

	if(plaetze[LESE]){
		SynBandEins::getInstance()->setMotorStop();
		//Timer pause
	}

}

void Uebergabesteuerung::transitionenAusfuehren(){

	if(plaetze[GZ] && !plaetze[LESE] && !eingang[LICHTSCHRANKE]){
		plaetze[GZ] = 0;
		plaetze[LESE] = 1;
		ladeWerkstueck();
	}

	if (plaetze[LESE] && !plaetze[WARTE_U] && eingang[READY]) {
		plaetze[LESE] = 0;
		plaetze[WARTE_U] = 1;
		SynBandEins::getInstance()->inkrementSynUebergabeStart();
	}

	if (plaetze[WARTE_U] && !plaetze[GZ] && SynBandEins::getInstance()->getSynUebergabeEnde()) {
		plaetze[WARTE_U] = 0;
		SynBandEins::getInstance()->dekrementSynUebergabeEnde();
		plaetze[GZ] = 1;
	}
}

void Uebergabesteuerung::execute(){
	transitionenAusfuehren();
	schreibeSignale();
}

}
