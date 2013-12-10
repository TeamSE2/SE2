/*
 * WeichenSteuerung.cpp
 *
 *  Created on: 24.11.2013
 *      Author: Pascal
 */

#include "Weichensteuerung.h"


namespace PetriNetzBandEins {

Weichensteuerung *Weichensteuerung::instance = NULL;

Weichensteuerung::Weichensteuerung() {
	initNetz();
	Dispatcher::getInstance()->anmelden(this, LICHTSCHRANKE_WEICHE, P_B);
}

Weichensteuerung::~Weichensteuerung() {
	Dispatcher::getInstance()->abmelden(this, LICHTSCHRANKE_WEICHE, P_B);
	delete instance;
	instance = NULL;
}

Weichensteuerung* Weichensteuerung::getInstance(){
	if(instance == NULL){
		instance = new Weichensteuerung();
	}

	return instance;
}

void Weichensteuerung::initNetz(){
	plaetze[GZ] = ANZ_MARKEN_W;
	plaetze[CHECK] = 0;
	plaetze[TB_1] = 0;
	plaetze[TB_2] = 0;
	plaetze[FLANKE_P] = 1;
	plaetze[FLANKE_N] = 0;
	plaetze[SYN_FLANKE] = 0;
}

void Weichensteuerung::ladeWerkstueck(){
	temp_ws = SynBandEins::getInstance()->popWerkstueckWeiche();
	if ((*temp_ws).typ == ZU_FLACH) {
		cout<< "zu flach" << endl;
		eingang[HOEHE] = 0;
	}else{
		cout<< "nicht zu flach" << endl;
		eingang[HOEHE] = 1;
	}
}

void Weichensteuerung::sendeWerkstueck(){
	SynBandEins::getInstance()->pushWerkstueckAuslauf(temp_ws);
	SynBandEins::getInstance()->pushWerkstueckUebergabe(temp_ws);
}

void Weichensteuerung::aktualisiereSignale(uint8_t iq, uint8_t state){

	 if(iq == LICHTSCHRANKE_WEICHE){
		 eingang[LICHTSCHRANKE] = state;
	 }
}



void Weichensteuerung::schreibeSignale(){
	if(plaetze[TB_1] || plaetze[TB_2]){
		HAL::getInstance().getWeiche()->auf(true);
	}else{
		HAL::getInstance().getWeiche()->auf(false);
	}
}

void Weichensteuerung::transitionenAusfuehren(){

	//Flanken detektor
	if(plaetze[FLANKE_P] && !plaetze[FLANKE_N] && !eingang[LICHTSCHRANKE]){
		plaetze[FLANKE_P] = 0;
		plaetze[SYN_FLANKE]= 1;
		plaetze[FLANKE_N] = 1;
		printf("1: FLANKE_P: %i, FLANKE_N: %i, SYN_FLANKE: % i,  \n"
				"GZ: %i, CHECK: %i, TB_1: %i, TB_2: %i\n"
				" \n",plaetze[FLANKE_P], plaetze[FLANKE_N], plaetze[SYN_FLANKE], plaetze[GZ],
					plaetze[CHECK], plaetze[TB_1], plaetze[TB_2]);

	}

	if(plaetze[FLANKE_N] && !plaetze[FLANKE_P] && eingang[LICHTSCHRANKE] ){
		plaetze[FLANKE_N] = 0;
		plaetze[FLANKE_P] = 1;
		printf("2: FLANKE_P: %i, FLANKE_N: %i, SYN_FLANKE: % i,  \n"
				"GZ: %i, CHECK: %i, TB_1: %i, TB_2: %i\n"
				" \n",plaetze[FLANKE_P], plaetze[FLANKE_N], plaetze[SYN_FLANKE], plaetze[GZ],
					plaetze[CHECK], plaetze[TB_1], plaetze[TB_2]);
	}

	// Weiche
	if(plaetze[SYN_FLANKE] && plaetze[GZ] && !plaetze[CHECK]){
		plaetze[SYN_FLANKE] = 0;
		plaetze[GZ] = plaetze[GZ] -1;
		plaetze[CHECK] = 1;

		ladeWerkstueck();
		printf("3: FLANKE_P: %i, FLANKE_N: %i, SYN_FLANKE: % i,  \n"
				"GZ: %i, CHECK: %i, TB_1: %i, TB_2: %i\n"
				" \n",plaetze[FLANKE_P], plaetze[FLANKE_N], plaetze[SYN_FLANKE], plaetze[GZ],
					plaetze[CHECK], plaetze[TB_1], plaetze[TB_2]);
	}

	if(plaetze[CHECK] && plaetze[GZ] < ANZ_MARKEN_W && eingang[LICHTSCHRANKE] && !eingang[HOEHE]){
		plaetze[CHECK] = 0;
		plaetze[GZ]++;
		SynBandEins::getInstance()->inkrementSynVerlassen();
		sendeWerkstueck();
		printf("4: FLANKE_P: %i, FLANKE_N: %i, SYN_FLANKE: % i,  \n"
				"GZ: %i, CHECK: %i, TB_1: %i, TB_2: %i\n"
				" \n",plaetze[FLANKE_P], plaetze[FLANKE_N], plaetze[SYN_FLANKE], plaetze[GZ],
					plaetze[CHECK], plaetze[TB_1], plaetze[TB_2]);
	}

	if(plaetze[CHECK] && !plaetze[TB_1] && eingang[HOEHE]){
		plaetze[CHECK] = 0;
		plaetze[TB_1] = 1;
		printf("5: FLANKE_P: %i, FLANKE_N: %i, SYN_FLANKE: % i,  \n"
				"GZ: %i, CHECK: %i, TB_1: %i, TB_2: %i\n"
				" \n",plaetze[FLANKE_P], plaetze[FLANKE_N], plaetze[SYN_FLANKE], plaetze[GZ],
					plaetze[CHECK], plaetze[TB_1], plaetze[TB_2]);
	}

	if(plaetze[TB_1] && !plaetze[TB_2] && eingang[LICHTSCHRANKE]){
		plaetze[TB_1] = 0;
		plaetze[TB_2] = 1;
		printf("6: FLANKE_P: %i, FLANKE_N: %i, SYN_FLANKE: % i,  \n"
				"GZ: %i, CHECK: %i, TB_1: %i, TB_2: %i\n"
				" \n",plaetze[FLANKE_P], plaetze[FLANKE_N], plaetze[SYN_FLANKE], plaetze[GZ],
					plaetze[CHECK], plaetze[TB_1], plaetze[TB_2]);
	}

	// todo: hier Timer Implementieren
	if(eingang[LICHTSCHRANKE] && plaetze[TB_2] && plaetze[GZ] < ANZ_MARKEN_W){
		plaetze[TB_2] = 0;
		plaetze[GZ]++;
		sendeWerkstueck();
		printf("7: FLANKE_P: %i, FLANKE_N: %i, SYN_FLANKE: % i,  \n"
				"GZ: %i, CHECK: %i, TB_1: %i, TB_2: %i\n"
				" \n",plaetze[FLANKE_P], plaetze[FLANKE_N], plaetze[SYN_FLANKE], plaetze[GZ],
					plaetze[CHECK], plaetze[TB_1], plaetze[TB_2]);
	}
}

void Weichensteuerung::execute(){
	transitionenAusfuehren();
	schreibeSignale();
}
}
