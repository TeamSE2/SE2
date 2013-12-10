#include "Einlaufsteuerung.h"

namespace PetriNetzBandEins{

Einlaufsteuerung *Einlaufsteuerung::instance = NULL;
long Einlaufsteuerung::werkstueck_id = 0;

Einlaufsteuerung::Einlaufsteuerung(){
//	cout << "Einlaufsteuerung: " << this << endl;
	initNetz();
	Dispatcher::getInstance()->anmelden(this, LICHTSCHRANKE_EINLAUF, P_B);
}

Einlaufsteuerung::~Einlaufsteuerung(){
	Dispatcher::getInstance()->abmelden(this, LICHTSCHRANKE_EINLAUF, P_B);

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
	plaetze[GZ] = ANZ_MARKEN_E;
	plaetze[EINLAUF] = 0;
	plaetze[WARTE_E] = 0;
}

void Einlaufsteuerung::aktualisiereSignale(uint8_t iq, uint8_t state){
 if(iq == LICHTSCHRANKE_EINLAUF){
	 lichtschranke_einlauf = state;
 }
}

void Einlaufsteuerung::registriereWerkstueck(){
	Werkstueck *neues_ws = NULL;
	neues_ws = (Werkstueck*) malloc(sizeof(Werkstueck));

	(*neues_ws).id = werkstueck_id;
	(*neues_ws).typ = ZU_FLACH;
	(*neues_ws).hoehen[0] = 0;
	(*neues_ws).hoehen[1] = 0;

	SynBandEins::getInstance()->pushWerkstueckHoehenmessung(neues_ws);
	werkstueck_id++;
}

void Einlaufsteuerung::schreibeSignale(){

	if(plaetze[EINLAUF]){
		registriereWerkstueck();
	}

	if(plaetze[GZ] == 6){
		cout << "kein rechtslauf" << endl;
		HAL::getInstance().getMotor()->rechtslauf(false);
	}else{
		cout << "rechtslauf" << endl;
		HAL::getInstance().getMotor()->rechtslauf(true);
	}
}

void Einlaufsteuerung::transitionenAusfuehren(){

	if(plaetze[GZ] && !lichtschranke_einlauf && !plaetze[EINLAUF]){
		plaetze[GZ]--;
		plaetze[EINLAUF] = 1;
		cout << "GZ" << endl;
	}

	if(plaetze[EINLAUF] && lichtschranke_einlauf){
		plaetze[EINLAUF] = 0;
		plaetze[WARTE_E]++;
		cout << "EINLAUF" << endl;
	}

	if (plaetze[WARTE_E] && SynBandEins::getInstance()->getSynVerlassen()) {
		plaetze[WARTE_E]--;
		SynBandEins::getInstance()->dekrementSynVerlassen();
		plaetze[GZ]++;

		cout << "WARTE_E" << endl;
	}
}

void Einlaufsteuerung::execute(){
	transitionenAusfuehren();
	schreibeSignale();
}
}
