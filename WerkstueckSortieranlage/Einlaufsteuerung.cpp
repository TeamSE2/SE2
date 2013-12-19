#include "Einlaufsteuerung.h"

namespace PetriNetzBandEins{

Einlaufsteuerung *Einlaufsteuerung::instance = NULL;
long Einlaufsteuerung::werkstueck_id = 0;

Einlaufsteuerung::Einlaufsteuerung(){
	initNetz();
	Dispatcher::getInstance()->anmelden(this);
}

Einlaufsteuerung::~Einlaufsteuerung(){
	Dispatcher::getInstance()->abmelden(this);
	delete instance;
	instance = NULL;
}

 Einlaufsteuerung* Einlaufsteuerung::getInstance(){
	if(instance == NULL){
		instance = new Einlaufsteuerung();
	}

	return instance;
}

void Einlaufsteuerung::initNetz(){
	werkstueck_id = 1;
	plaetze[GZ] = ANZ_MARKEN_E;
	plaetze[EINLAUF] = 0;
	plaetze[WARTE_E] = 0;
	lichtschranke_einlauf = 1;
}

bool Einlaufsteuerung::aktualisiereSignale(uint8_t port, uint8_t iq, uint8_t state){
	bool execute = false;

	if(port == P_B){
		if(iq == LICHTSCHRANKE_EINLAUF){
			lichtschranke_einlauf = state;
			execute = true;
		}
	}

	if(port == SYN_BAND_EINS){
		if(iq == VERLASSEN){
			execute = true;
		}
	}

	return execute;

}

void Einlaufsteuerung::registriereWerkstueck(){
	WerkstueckDaten *neues_ws = NULL;

	neues_ws = (WerkstueckDaten*) malloc(sizeof(WerkstueckDaten));

	(*neues_ws).id = (werkstueck_id % MAX_ID);
	(*neues_ws).typ = ZU_FLACH;
	(*neues_ws).hoehen[0] = 0;
	(*neues_ws).hoehen[1] = 0;

	SynBandEins::getInstance()->pushWerkstueckHoehenmessung(neues_ws);
	werkstueck_id++;
}

void Einlaufsteuerung::schreibeSignale(){
	if(plaetze[GZ] == 6){
		HAL::getInstance().getMotor()->rechtslauf(false);
	}else{
		HAL::getInstance().getMotor()->rechtslauf(true);
	}
}

void Einlaufsteuerung::transitionenAusfuehren(){

	if(plaetze[GZ] && !plaetze[EINLAUF] && !lichtschranke_einlauf){
		plaetze[GZ]--;
		plaetze[EINLAUF] = 1;
		registriereWerkstueck();
		printf("Einlauf: GZ: %i, EINLAUF: %i, WARTE_E: %i \n",plaetze[GZ], plaetze[EINLAUF], plaetze[WARTE_E]);
	}

	if(plaetze[EINLAUF] && lichtschranke_einlauf){
		plaetze[EINLAUF] = 0;
		plaetze[WARTE_E]++;
		printf("Einlauf: GZ: %i, EINLAUF: %i, WARTE_E: %i \n",plaetze[GZ], plaetze[EINLAUF], plaetze[WARTE_E]);
	}

	if (plaetze[WARTE_E] && SynBandEins::getInstance()->getSynVerlassen()) {
		plaetze[WARTE_E]--;
		SynBandEins::getInstance()->dekrementSynVerlassen();
		plaetze[GZ]++;
		printf("Einlauf: GZ: %i, EINLAUF: %i, WARTE_E: %i \n",plaetze[GZ], plaetze[EINLAUF], plaetze[WARTE_E]);

	}
}

void Einlaufsteuerung::execute(){
	transitionenAusfuehren();
	schreibeSignale();
}
}
