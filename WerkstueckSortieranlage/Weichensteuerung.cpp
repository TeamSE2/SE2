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
	Dispatcher::getInstance()->anmelden(this);}

Weichensteuerung::~Weichensteuerung() {
	Dispatcher::getInstance()->abmelden(this);	delete instance;
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
	eingang[LICHTSCHRANKE] = 1;
	eingang[RUTSCHE] = 1;
	eingang[TIMER_INT] = 0;
	timer.tv_nsec = 800000000;
	timer.tv_sec = 0;

}

void Weichensteuerung::ladeWerkstueck(){
	static int toggle = 0;

	temp_ws[toggle] = SynBandEins::getInstance()->popWerkstueckWeiche();
	if(temp_ws[toggle] != NULL){
		if ((*temp_ws[toggle]).typ == ZU_FLACH) {
			eingang[HOEHE] = 0;
		}else{
			eingang[HOEHE] = 1;
		}

		toggle = (toggle + 1) % ANZ_MARKEN_W;
	}
}

void Weichensteuerung::sendeWerkstueck(){
	static int toggle = 0;

	SynBandEins::getInstance()->pushWerkstueckAuslauf(temp_ws[toggle]);
	SynBandEins::getInstance()->pushWerkstueckUebergabe(temp_ws[toggle]);

	temp_ws[toggle] = NULL;
	toggle = (toggle + 1) % ANZ_MARKEN_W;
}

bool Weichensteuerung::aktualisiereSignale(uint8_t port, uint8_t iq, uint8_t state){
	bool execute = false;

	if(port == P_B){
		if(iq == LICHTSCHRANKE_WEICHE){
			eingang[LICHTSCHRANKE] = state;
			execute = true;
		}
	}

	if(port == P_B){
		switch (iq) {
				case LICHTSCHRANKE_WEICHE:
					eingang[LICHTSCHRANKE] = state;
					execute = true;
					break;
				case RUTSCHE_VOLL:
					eingang[RUTSCHE] = state;
					execute = true;
				default:
					break;
			}
	}

	 if(port == TIMER_PULSE_CODE){
 		 if(iq == timer_id[0] || iq == timer_id[1] || iq == timer_id[2]){
 			 cout << "test" << endl;
			 eingang[TIMER_INT]++;
			 execute = true;
		 }
	 }

	 return execute;
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
			printf("Weiche: 1: FLANKE_P: %i, FLANKE_N: %i, SYN_FLANKE: % i,  \n"
					"GZ: %i, CHECK: %i, TB_1: %i, TB_2: %i\n"
					" \n",plaetze[FLANKE_P], plaetze[FLANKE_N], plaetze[SYN_FLANKE], plaetze[GZ],
						plaetze[CHECK], plaetze[TB_1], plaetze[TB_2]);

		}

		if(plaetze[FLANKE_N] && !plaetze[FLANKE_P] && eingang[LICHTSCHRANKE] ){
			plaetze[FLANKE_N] = 0;
			plaetze[FLANKE_P] = 1;
			printf("Weiche: 2: FLANKE_P: %i, FLANKE_N: %i, SYN_FLANKE: % i,  \n"
					"GZ: %i, CHECK: %i, TB_1: %i, TB_2: %i\n"
					" \n",plaetze[FLANKE_P], plaetze[FLANKE_N], plaetze[SYN_FLANKE], plaetze[GZ],
						plaetze[CHECK], plaetze[TB_1], plaetze[TB_2]);
		}

		// Weiche
		if(plaetze[SYN_FLANKE] && plaetze[GZ] && !plaetze[CHECK]){
			ladeWerkstueck();
			if(temp_ws[0] != NULL || temp_ws[1] != NULL){
				plaetze[SYN_FLANKE] = 0;
				plaetze[GZ]--;
				plaetze[CHECK] = 1;
			}


			printf("Weiche: 3: FLANKE_P: %i, FLANKE_N: %i, SYN_FLANKE: % i,  \n"
					"GZ: %i, CHECK: %i, TB_1: %i, TB_2: %i\n"
					" \n",plaetze[FLANKE_P], plaetze[FLANKE_N], plaetze[SYN_FLANKE], plaetze[GZ],
						plaetze[CHECK], plaetze[TB_1], plaetze[TB_2]);
		}

	if(temp_ws[0] != NULL || temp_ws[1] != NULL){
		if(plaetze[CHECK] && !plaetze[CHECK_R] && eingang[LICHTSCHRANKE] && !eingang[HOEHE]){
			plaetze[CHECK] = 0;
			plaetze[CHECK_R] = 1;
			printf("Weiche: 4: FLANKE_P: %i, FLANKE_N: %i, SYN_FLANKE: % i,  \n"
					"GZ: %i, CHECK: %i, TB_1: %i, TB_2: %i\n"
					" \n",plaetze[FLANKE_P], plaetze[FLANKE_N], plaetze[SYN_FLANKE], plaetze[GZ],
						plaetze[CHECK], plaetze[TB_1], plaetze[TB_2]);
		}

		if(plaetze[CHECK_R] && plaetze[GZ] < ANZ_MARKEN_W && !eingang[RUTSCHE]){
			plaetze[CHECK_R] = 0;
			plaetze[GZ]++;
			SynBandEins::getInstance()->inkrementSynVerlassen();
			printf("Weiche: 4: FLANKE_P: %i, FLANKE_N: %i, SYN_FLANKE: % i,  \n"
					"GZ: %i, CHECK: %i, TB_1: %i, TB_2: %i\n"
					" \n",plaetze[FLANKE_P], plaetze[FLANKE_N], plaetze[SYN_FLANKE], plaetze[GZ],
						plaetze[CHECK], plaetze[TB_1], plaetze[TB_2]);
		}

		if(plaetze[CHECK] && !plaetze[TB_1] && eingang[HOEHE]){
			plaetze[CHECK] = 0;
			plaetze[TB_1] = 1;
			printf("Weiche: 5: FLANKE_P: %i, FLANKE_N: %i, SYN_FLANKE: % i,  \n"
					"GZ: %i, CHECK: %i, TB_1: %i, TB_2: %i\n"
					" \n",plaetze[FLANKE_P], plaetze[FLANKE_N], plaetze[SYN_FLANKE], plaetze[GZ],
						plaetze[CHECK], plaetze[TB_1], plaetze[TB_2]);
		}

		if(plaetze[TB_1] && plaetze[TB_2] < ANZ_MARKEN_W && eingang[LICHTSCHRANKE]){
			plaetze[TB_1] = 0;
			plaetze[TB_2]++;
			timer_id[timer_index] = Timer::starten(timer);
			timer_index = (timer_index + 1) % ANZ_MARKEN_W;
			sendeWerkstueck();
			SynBandEins::getInstance()->inkrementSynUebergabeStart();
			printf("Weiche: 6: FLANKE_P: %i, FLANKE_N: %i, SYN_FLANKE: % i,  \n"
					"GZ: %i, CHECK: %i, TB_1: %i, TB_2: %i\n"
					" \n",plaetze[FLANKE_P], plaetze[FLANKE_N], plaetze[SYN_FLANKE], plaetze[GZ],
						plaetze[CHECK], plaetze[TB_1], plaetze[TB_2]);
		}

		// todo: hier Timer Implementieren
		if(plaetze[TB_2] && plaetze[GZ] < ANZ_MARKEN_W && eingang[TIMER_INT]){
			plaetze[TB_2]--;
			plaetze[GZ]++;
			printf("Weiche: 7: FLANKE_P: %i, FLANKE_N: %i, SYN_FLANKE: % i,  \n"
					"GZ: %i, CHECK: %i, TB_1: %i, TB_2: %i\n"
					" \n",plaetze[FLANKE_P], plaetze[FLANKE_N], plaetze[SYN_FLANKE], plaetze[GZ],
						plaetze[CHECK], plaetze[TB_1], plaetze[TB_2]);
		}
	}

}

void Weichensteuerung::execute(){
	transitionenAusfuehren();
	schreibeSignale();
}
}
