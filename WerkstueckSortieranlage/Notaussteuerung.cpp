/*
 * Fehlersteuerung.cpp
 *
 *  Created on: 15.12.2013
 *      Author: Pascal
 */

#include "Notaussteuerung.h"

namespace PetriNetzBandEins{

Notaussteuerung *Notaussteuerung::instance = NULL;

Notaussteuerung::Notaussteuerung(){
	initNetz();
	Dispatcher::getInstance()->anmelden(this);

}

Notaussteuerung::~Notaussteuerung(){
	Dispatcher::getInstance()->abmelden(this);
	delete instance;
	instance = NULL;
}

Notaussteuerung* Notaussteuerung::getInstance(){

	if(instance == NULL){
		instance = new Notaussteuerung();
	}

	return instance;
}

bool Notaussteuerung::aktualisiereSignale(uint8_t port, uint8_t iq, uint8_t state){
	bool execute = false;

	if(port == P_B){
		switch (iq) {
				case LICHTSCHRANKE_EINLAUF:
					eingaenge[LS_E] = state;
					execute = true;
					break;
				case LICHTSCHRANKE_WEICHE:
					eingaenge[LS_W] = state;
					execute = true;
					break;
				case LICHTSCHRANKE_HOEHENMESSUNG:
					eingaenge[LS_H] = state;
					execute = true;
					break;
				case LICHTSCHRANKE_AUSLAUF:
					eingaenge[LS_A] = state;
					execute = true;
					break;
				case RUTSCHE_VOLL:
					eingaenge[LS_R] = state;
					execute = true;
					break;
				default:
					break;
			}
	}

	if(port == P_C){
		switch (iq) {
			case TASTE_RESET:
				eingaenge[RESET_L] = state;
				execute = true;
				break;
			case TASTE_ESTOPP:
				eingaenge[NOTAUS_L] = state;
				execute = true;
				break;
			default:
				break;
		}
	}

	if(port == FEHLER){
		switch (iq) {
			case RESET_P:
				eingaenge[RESET_G] = 1;
				execute = true;
				break;
			case RESET_N:
				eingaenge[RESET_G] = 0;
				execute = true;
				break;
			case ESTOPP_P:
				eingaenge[NOTAUS_G] = 1;
				execute = true;
				break;
			case ESTOPP_N:
				eingaenge[NOTAUS_G] = 0;
				execute = true;
				break;
			default:
				break;
		}
	}

	return execute;

}

void Notaussteuerung::initNetz(){
	plaetze[GZ] = 1;
	plaetze[FEHLER_L] = 0;
	plaetze[RESET_L1] = 0;
	plaetze[RESET_L2] = 0;
	plaetze[FEHLER_G] = 0;
	plaetze[RESET_G1] = 0;
	plaetze[RESET_G2] = 0;

	plaetze[RESET_L] = 0;
	plaetze[RESET_G] = 0;
	plaetze[NOTAUS_L] = 1;
	plaetze[NOTAUS_G] = 1;
	eingaenge[LS_E] = 1;
	eingaenge[LS_H] = 1;
	eingaenge[LS_W] = 1;
	eingaenge[LS_A] = 1;
	eingaenge[LS_R] = 1;
}

void Notaussteuerung::schreibeSignale(){

	if(plaetze[RESET_L2] || plaetze[RESET_G2]){
		SynBandEins::getInstance()->resetNetz();
	}

	if(plaetze[FEHLER_L] ||plaetze[RESET_L1] || plaetze[RESET_L2] || plaetze[FEHLER_G] ||plaetze[RESET_G1] || plaetze[RESET_G2]){
		SynBandEins::getInstance()->setMotorStop();
	}

	if( plaetze[RESET_L1] || plaetze[RESET_L1] || plaetze[RESET_L1] || plaetze[RESET_G1]){
		SynBandEins::getInstance()->setResetLED();
	}
}

void Notaussteuerung::transitionenAusfuehren(){

	fehlerBehandlung(plaetze[FEHLER_L], plaetze[RESET_L1], plaetze[RESET_L2], eingaenge[NOTAUS_L], eingaenge[RESET_L]);
	fehlerBehandlung(plaetze[FEHLER_G], plaetze[RESET_G1], plaetze[RESET_G2], eingaenge[NOTAUS_G], eingaenge[RESET_G]);
}

void Notaussteuerung::fehlerBehandlung(uint8_t fehler, uint8_t reset_1, uint8_t reset_2, uint8_t notaus, uint8_t reset){
	if(plaetze[GZ] && !plaetze[fehler] && !eingaenge[notaus]){
		plaetze[GZ] = 0;
		plaetze[fehler] = 1;
		if(notaus == NOTAUS_G){
			SerielleSchnittstelle::getInstance().sendeNachricht(ESTOPP_N);
		}
	}

	if(plaetze[fehler] && !plaetze[reset_1] && eingaenge[notaus] && eingaenge[LS_E] && eingaenge[LS_H] && eingaenge[LS_W] && eingaenge[LS_A] && eingaenge[LS_R]){
		plaetze[fehler] = 0;
		plaetze[reset_1] = 1;
		if(notaus == NOTAUS_G){
			SerielleSchnittstelle::getInstance().sendeNachricht(ESTOPP_P);
		}
	}

	if(plaetze[reset_1] && !plaetze[reset_2] && eingaenge[reset]){
		plaetze[reset_1] = 0;
		plaetze[reset] = 1;
		if(notaus == NOTAUS_G){
			SerielleSchnittstelle::getInstance().sendeNachricht(RESET_P);
		}
	}

	if(plaetze[reset_2] && !plaetze[GZ] && !eingaenge[reset]){
		plaetze[reset_2] = 0;
		plaetze[GZ]++;
		if(notaus == NOTAUS_G){
			SerielleSchnittstelle::getInstance().sendeNachricht(RESET_N);
		}
	}
}

void Notaussteuerung::execute(){
	transitionenAusfuehren();
	schreibeSignale();
}

}
