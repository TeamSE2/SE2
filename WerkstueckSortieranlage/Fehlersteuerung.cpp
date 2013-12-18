/*
 * Fehlersteuerung.cpp
 *
 *  Created on: 15.12.2013
 *      Author: Pascal
 */

#include "Fehlersteuerung.h"
#include "WerkstueckDaten.h"
#include "PulsNachricht.h"

namespace PetriNetzBandEins {

Fehlersteuerung *Fehlersteuerung::instance = NULL;

Fehlersteuerung::Fehlersteuerung() {
	initNetz();
	Dispatcher::getInstance()->anmelden(this);
}

Fehlersteuerung::~Fehlersteuerung() {
	Dispatcher::getInstance()->abmelden(this);
	delete instance;
	instance = NULL;
}

Fehlersteuerung* Fehlersteuerung::getInstance() {

	if (instance == NULL) {
		instance = new Fehlersteuerung();
	}

	return instance;
}

bool Fehlersteuerung::aktualisiereSignale(uint8_t port, uint8_t iq,
		uint8_t state) {
	bool execute = false;

	if (port == P_B) {
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

	if (port == P_C) {
		if (iq == TASTE_RESET) {
			eingaenge[RESET] = state;
			execute = true;
		}
	}

	if (port == TIMER_PULSE_CODE) {
//
//		switch (iq) {
//		case IQ_E:
//			eingaenge[TIMER_INT_E] = 1;
//			execute = true;
//			break;
//		case IQ_H:
//			eingaenge[TIMER_INT_H] = 1;
//			execute = true;
//			break;
//		case IQ_W:
//			eingaenge[TIMER_INT_W] = 1;
//			execute = true;
//			break;
//		case IQ_A:
//			eingaenge[TIMER_INT_A] = 1;
//			execute = true;
//			break;
//		case IQ_R:
//			eingaenge[TIMER_INT_R] = 1;
//			execute = true;
//			break;
//		default:
//			break;
//		}

		if (iq == ws_h->timer_id) {
			eingaenge[TIMER_INT_WS_H] = 1;
			execute = true;
		}

		if (iq == ws_w->timer_id) {
			eingaenge[TIMER_INT_WS_W] = 1;
			execute = true;
		}

		if (iq == ws_a->timer_id) {
			eingaenge[TIMER_INT_WS_A] = 1;
			execute = true;
		}
	}

	return execute;

}

void Fehlersteuerung::initNetz() {
	plaetze[GZ] = ANZ_MARKEN_F;
	plaetze[CHECK_TB_H] = 0;
	plaetze[CHECK_TB_W] = 0;
	plaetze[CHECK_TB_A] = 0;
	plaetze[FEHLER_F] = 0;
	plaetze[RESET_1] = 0;
	plaetze[RESET_2] = 0;
	plaetze[RESET_R2] = 0;

	plaetze[CHECK_E] = 0;
	plaetze[CHECK_H] = 0;
	plaetze[CHECK_W] = 0;
	plaetze[CHECK_A] = 0;
	plaetze[CHECK_RV] = 0;

	eingaenge[LS_E] = 1;
	eingaenge[LS_H] = 1;
	eingaenge[LS_W] = 1;
	eingaenge[LS_A] = 1;
	eingaenge[LS_R] = 1;
	eingaenge[TIMER_INT_E] = 0;
	eingaenge[TIMER_INT_H] = 0;
	eingaenge[TIMER_INT_W] = 0;
	eingaenge[TIMER_INT_A] = 0;
	eingaenge[TIMER_INT_R] = 0;
	eingaenge[TIMER_INT_WS_H] = 0;
	eingaenge[TIMER_INT_WS_W] = 0;
	eingaenge[TIMER_INT_WS_A] = 0;
}

void Fehlersteuerung::ladeWerkstueckHoehenmessung() {

	WerkstueckDaten *neues_ws = NULL;

	neues_ws = (WerkstueckDaten*) malloc(sizeof(WerkstueckDaten));

	(*neues_ws).id = 1;
	(*neues_ws).typ = ZU_FLACH;
	(*neues_ws).hoehen[0] = 0;
	(*neues_ws).hoehen[1] = 0;
	this->ws_h = neues_ws;
//	this->ws_h = SynBandEins::getInstance()->getWerkstueckHoehenmessung();
}

void Fehlersteuerung::ladeWerkstueckWeiche() {

	WerkstueckDaten *neues_ws = NULL;

	neues_ws = (WerkstueckDaten*) malloc(sizeof(WerkstueckDaten));

	(*neues_ws).id = 2;
	(*neues_ws).typ = ZU_FLACH;
	(*neues_ws).hoehen[0] = 0;
	(*neues_ws).hoehen[1] = 0;
	this->ws_h = neues_ws;
//	this->ws_h = SynBandEins::getInstance()->getWerkstueckWeiche();
}

void Fehlersteuerung::ladeWerkstueckAuslauf() {

	WerkstueckDaten *neues_ws = NULL;

	neues_ws = (WerkstueckDaten*) malloc(sizeof(WerkstueckDaten));

	(*neues_ws).id = 3;
	(*neues_ws).typ = ZU_FLACH;
	(*neues_ws).hoehen[0] = 0;
	(*neues_ws).hoehen[1] = 0;
	this->ws_h = neues_ws;
//	this->ws_h = SynBandEins::getInstance()->getWerkstueckAuslauf();
}

void Fehlersteuerung::schreibeSignale() {

	if (plaetze[RESET_2]) {
		SynBandEins::getInstance()->resetNetz();
	}

	if (plaetze[FEHLER_F] || plaetze[RESET_1] || plaetze[RESET_2]
			|| plaetze[RESET_R2]) {
		SynBandEins::getInstance()->setMotorStop();
	}

	if (plaetze[RESET_1]) {
		SynBandEins::getInstance()->setResetLED();
	}
}

void Fehlersteuerung::transitionenAusfuehren() {
	lichtschrankeEinlauf();
	lichtschrankeHoehenmessung();
	lichtschrankeWeiche();
	lichtschrankeAuslauf();

	fehlerBehandlung(RESET_2);
	fehlerBehandlung(RESET_R2);

}

void Fehlersteuerung::lichtschrankeEinlauf() {
	lichtschrankeTimerFehler(LS_E, TIMER_INT_E, CHECK_E);
}

void Fehlersteuerung::lichtschrankeHoehenmessung() {
	werkstueckTimerFehler(LS_H, TIMER_INT_WS_H, CHECK_TB_H, TB_H);
	lichtschrankeTimerFehler(LS_H, TIMER_INT_H, CHECK_H);
}

void Fehlersteuerung::lichtschrankeWeiche() {
	werkstueckTimerFehler(LS_W, TIMER_INT_WS_W, CHECK_TB_W, TB_W);
	lichtschrankeTimerFehler(LS_W, TIMER_INT_W, CHECK_W);
}

void Fehlersteuerung::lichtschrankeAuslauf() {
	werkstueckTimerFehler(LS_A, TIMER_INT_WS_A, CHECK_TB_A, TB_A);
	lichtschrankeTimerFehler(LS_A, TIMER_INT_A, CHECK_A);
}

void Fehlersteuerung::lichtschrankeRutsche() {
	lichtschrankeTimerFehler(LS_R, TIMER_INT_R, CHECK_RV);
}

void Fehlersteuerung::werkstueckTimerFehler(uint8_t ls, uint8_t timer_int_ws,
		uint8_t check_tb, uint8_t tb) {
	//Werkstueck zu frueh oder zu spaet
	if (plaetze[GZ] && !plaetze[check_tb] && !eingaenge[ls]) {
		plaetze[GZ]--;
		plaetze[check_tb] = 1;

		//todo: Tolleranzbereich checken
		switch (timer_int_ws) {
		case TIMER_INT_WS_H:
			ladeWerkstueckHoehenmessung();
			eingaenge[TB_H] = checkToleranzbereich(Timer::gettime(ws_h->timer_id), 500);
			break;
		case TIMER_INT_WS_W:
			ladeWerkstueckWeiche();
			eingaenge[TB_W] = checkToleranzbereich(Timer::gettime(ws_w->timer_id), 500);
			break;
		case TIMER_INT_WS_A:
			ladeWerkstueckAuslauf();
			eingaenge[TB_A] = checkToleranzbereich(Timer::gettime(ws_a->timer_id), 500);
			break;
		default:
			break;
		}

	}

	if (plaetze[GZ] && !plaetze[FEHLER_F] && eingaenge[timer_int_ws]) {
		plaetze[GZ]--;
		plaetze[FEHLER_F] = 1;
		switch (timer_int_ws) {
		case TIMER_INT_WS_H:
			eingaenge[TIMER_INT_WS_H] = 0;
			break;
		case TIMER_INT_WS_W:
			eingaenge[TIMER_INT_WS_W] = 0;
			break;
		case TIMER_INT_WS_A:
			eingaenge[TIMER_INT_WS_A] = 0;
			break;
		default:
			break;
		}
	}

	if (plaetze[check_tb] && !plaetze[FEHLER_F] && !eingaenge[tb]) {
		plaetze[check_tb] = 0;
		plaetze[FEHLER_F] = 1;
	}

	if (plaetze[check_tb] && plaetze[GZ] < ANZ_MARKEN_F && eingaenge[tb]) {
		plaetze[check_tb] = 0;
		plaetze[GZ]++;
	}
}

void Fehlersteuerung::lichtschrankeTimerFehler(uint8_t ls, uint8_t timer_int,
		uint8_t check) {

	if (plaetze[GZ] && !plaetze[check] && !eingaenge[ls]) {
		plaetze[GZ]--;
		plaetze[check] = 1;
		printf("\n LS FEHLER 1: GZ: %i, CHECK: %i, FEHLER: %i \n",plaetze[GZ], plaetze[check], plaetze[FEHLER_F]);
		ls_timer_id[ls] = Timer::starten(ls_timer[ls]);

	}

	if (plaetze[check] && plaetze[GZ] < ANZ_MARKEN_F && eingaenge[ls]) {
		plaetze[check] = 0;
		plaetze[GZ]++;
		printf("\n LS FEHLER 2: GZ: %i, CHECK: %i, FEHLER: %i \n",plaetze[GZ], plaetze[check], plaetze[FEHLER_F]);
	}

	if (plaetze[check] && !plaetze[FEHLER_F] && eingaenge[timer_int]) {
		plaetze[check] = 0;
		plaetze[FEHLER_F] = 1;
		printf("\n LS FEHLER 3: GZ: %i, CHECK: %i, FEHLER: %i \n",plaetze[GZ], plaetze[check], plaetze[FEHLER_F]);
		switch (timer_int) {
		case TIMER_INT_E:
			eingaenge[TIMER_INT_E] = 0;
			break;
		case TIMER_INT_H:
			eingaenge[TIMER_INT_H] = 0;
			break;
		case TIMER_INT_W:
			eingaenge[TIMER_INT_W] = 0;
			break;
		case TIMER_INT_A:
			eingaenge[TIMER_INT_A] = 0;
			break;
		case TIMER_INT_R:
			eingaenge[TIMER_INT_R] = 0;
			break;
		default:
			break;
		}
	}
}

void Fehlersteuerung::fehlerBehandlung(uint8_t reset_2) {

	if (reset_2 == RESET_R2) {

		if (plaetze[FEHLER_F] && !plaetze[RESET_1] && eingaenge[LS_R]) {
			plaetze[FEHLER_F] = 0;
			plaetze[RESET_1] = 1;
			printf("\nFehlerbehandlung 1.1: GZ: %i, FEHLER: %i, RESET_1: %i, RESET_2: %i",plaetze[GZ], plaetze[FEHLER_F], plaetze[RESET_1], plaetze[RESET_2]);

		}

	} else {

		if (plaetze[FEHLER_F] && !plaetze[RESET_1] && eingaenge[LS_E]
				&& eingaenge[LS_H] && eingaenge[LS_W] && eingaenge[LS_A]
				&& eingaenge[LS_R]) {
			plaetze[FEHLER_F] = 0;
			plaetze[RESET_1] = 1;
			printf("\nFehlerbehandlung 1.2: GZ: %i, FEHLER: %i, RESET_1: %i, RESET_2: %i",plaetze[GZ], plaetze[FEHLER_F], plaetze[RESET_1], plaetze[RESET_2]);

		}

	}

	if (plaetze[RESET_1] && !plaetze[reset_2] && eingaenge[RESET]) {
		plaetze[RESET_1] = 0;
		plaetze[reset_2] = 1;
		printf("\nFehlerbehandlung 2: GZ: %i, FEHLER: %i, RESET_1: %i, RESET_2: %i",plaetze[GZ], plaetze[FEHLER_F], plaetze[RESET_1], plaetze[RESET_2]);

	}

	if (plaetze[reset_2] && plaetze[GZ] < ANZ_MARKEN_F && !eingaenge[RESET]) {
		plaetze[reset_2] = 0;
		plaetze[GZ]++;
		printf("\nFehlerbehandlung 3: GZ: %i, FEHLER: %i, RESET_1: %i, RESET_2: %i",plaetze[GZ], plaetze[FEHLER_F], plaetze[RESET_1], plaetze[RESET_2]);

	}
}

bool Fehlersteuerung::checkToleranzbereich(timespec timer, int tb) {
	return (timer.tv_nsec - tb) > 0 ? false : true;
}

void Fehlersteuerung::execute(){
	transitionenAusfuehren();
	schreibeSignale();
}

}
