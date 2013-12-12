
#include "Detektorsteuerung.h"

namespace PetriNetzBandEins {

Detektorsteuerung *Detektorsteuerung::instance = NULL;

Detektorsteuerung::Detektorsteuerung(){
	initNetz();
	Dispatcher::getInstance()->anmelden(this);}

Detektorsteuerung::~Detektorsteuerung(){
	Dispatcher::getInstance()->abmelden(this);
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
	eingang[LICHTSCHRANKE] = 1;
	eingang[METALL] = 0;
}

void Detektorsteuerung::ladeWerkstueck(){
	temp_ws = SynBandEins::getInstance()->popWerkstueckDetektor();
}

bool Detektorsteuerung::aktualisiereSignale(uint8_t port, uint8_t iq, uint8_t state){
	bool execute;

	if(port == P_B){
		switch (iq) {
			case LICHTSCHRANKE_WEICHE:
				eingang[LICHTSCHRANKE] = state;
				execute = true;
				break;
			case METALLDETEKTOR_CHECK:
				eingang[METALL] = state;
				execute = true;
			default:
				break;
		}
	}

	return execute;
}

void Detektorsteuerung::schreibeSignale(){
	if (plaetze[WARTE]) {
		cout << "Metall!!!!"<< endl;
		(*temp_ws).typ = BOHRUNG_OBEN_METALL;
	}
}

void Detektorsteuerung::transitionenAusfuehren(){

	if (plaetze[GZ] && !plaetze[CHECK_M] && !eingang[LICHTSCHRANKE]) {
		plaetze[GZ] = 0;
		plaetze[CHECK_M] = 1;
		ladeWerkstueck();
		printf("1: GZ: %i, CHECK_M: %i, WARTE: %i ",plaetze[GZ], plaetze[CHECK_M], plaetze[WARTE]);
	}

	if (plaetze[CHECK_M] && !plaetze[GZ] && eingang[LICHTSCHRANKE]) {
		plaetze[CHECK_M] = 0;
		plaetze[GZ] = 1;
		printf("2: GZ: %i, CHECK_M: %i, WARTE: %i ",plaetze[GZ], plaetze[CHECK_M], plaetze[WARTE]);
	}

	if (plaetze[CHECK_M] && !plaetze[WARTE] && eingang[METALL]) {
		plaetze[CHECK_M] = 0;
		plaetze[WARTE] = 1;
		printf("3: GZ: %i, CHECK_M: %i, WARTE: %i ",plaetze[GZ], plaetze[CHECK_M], plaetze[WARTE]);
	}

	if (plaetze[WARTE] && !plaetze[GZ] && eingang[LICHTSCHRANKE]) {
		plaetze[WARTE] = 0;
		plaetze[GZ] = 1;
		printf("4: GZ: %i, CHECK_M: %i, WARTE: %i ",plaetze[GZ], plaetze[CHECK_M], plaetze[WARTE]);
	}
}

void Detektorsteuerung::execute(){
		transitionenAusfuehren();
		schreibeSignale();
}

}

