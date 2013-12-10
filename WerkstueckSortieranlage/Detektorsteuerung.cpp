
#include "Detektorsteuerung.h"

namespace PetriNetzBandEins {

Detektorsteuerung *Detektorsteuerung::instance = NULL;

Detektorsteuerung::Detektorsteuerung(){
	Dispatcher::getInstance()->anmelden(this, LICHTSCHRANKE_WEICHE, P_B);
	Dispatcher::getInstance()->anmelden(this, METALLDETEKTOR_CHECK, P_B);
}

Detektorsteuerung::~Detektorsteuerung(){
	Dispatcher::getInstance()->abmelden(this, LICHTSCHRANKE_WEICHE, P_B);
	Dispatcher::getInstance()->abmelden(this, METALLDETEKTOR_CHECK, P_B);

	delete instance;
	instance = NULL;
}

Detektorsteuerung* Detektorsteuerung::getInstance(){
	if(instance == NULL){
		instance = new Detektorsteuerung();
	}

	return instance;
}

void Detektorsteuerung::initNetz(){
	plaetze[GZ] = 1;
	plaetze[CHECK_M] = 0;
	plaetze[WARTE] = 0;
}

void Detektorsteuerung::ladeWerkstueck(){
	temp_ws = SynBandEins::getInstance()->popWerkstueckDetektor();
}

void Detektorsteuerung::aktualisiereSignale(uint8_t iq, uint8_t state){

	switch (iq) {
		case LICHTSCHRANKE_WEICHE:
			eingang[LICHTSCHRANKE] = state;
			break;
		case METALLDETEKTOR_CHECK:
			eingang[METALL] = state;
		default:
			break;
	}
}

void Detektorsteuerung::schreibeSignale(){
	if (plaetze[WARTE]) {
		(*temp_ws).typ = BOHRUNG_OBEN_METALL;
	}
}

void Detektorsteuerung::transitionenAusfuehren(){
	if (plaetze[GZ] && !plaetze[CHECK_M] && !eingang[LICHTSCHRANKE]) {
		plaetze[GZ] = 0;
		plaetze[CHECK_M] = 1;
		ladeWerkstueck();
	}

	if (plaetze[CHECK_M] && !plaetze[GZ] && eingang[LICHTSCHRANKE]) {
		plaetze[CHECK_M] = 0;
		plaetze[GZ] = 1;
	}

	if (plaetze[CHECK_M] && !plaetze[WARTE] && eingang[METALL]) {
		plaetze[CHECK_M] = 0;
		plaetze[WARTE] = 1;
	}

	if (plaetze[WARTE] && !plaetze[GZ] && eingang[LICHTSCHRANKE]) {
		plaetze[WARTE] = 0;
		plaetze[GZ] = 1;
	}
}

void Detektorsteuerung::execute(){
		transitionenAusfuehren();
		schreibeSignale();
}

}

