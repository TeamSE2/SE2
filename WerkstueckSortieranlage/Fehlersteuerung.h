#ifndef FEHLERSTEUERUNG_H
#define FEHLERSTEUERUNG_H


#include <stdint.h>
#include <stdlib.h>
#include "Beobachter.h"
#include "Dispatcher.h"
#include "WerkstueckDaten.h"
#include "SynBandEins.h"
#include "HAL.h"
#include "Timer.h"

//zeiten
#define LS_UNTERBRECHUNGS_ZEIT 3 // todo: zeit ermitteln
#define LS_TOLERANZBEREICH 1 // todo: zeit ermitteln
//init
#define ANZ_PLAETZE_F 13
#define ANZ_EINGAENGE_F 17
#define ANZ_MARKEN_F 5

// Plaetze
#define GZ 0
#define CHECK_TB_H 1
#define CHECK_TB_W 2
#define CHECK_TB_A 3
#define CHECK_E 4
#define CHECK_H 5
#define CHECK_W 6
#define CHECK_A 7
#define CHECK_RV 8
#define FEHLER_F 9
#define RESET_1 10
#define RESET_2 11
#define RESET_R2 12

//eingaenge
#define LS_E 0
#define LS_H 1
#define LS_W 2
#define LS_A 3
#define LS_R 4

#define TIMER_INT_E 5
#define TIMER_INT_H 6
#define TIMER_INT_W 7
#define TIMER_INT_A 8
#define TIMER_INT_R 9

#define TIMER_INT_WS_H 10
#define TIMER_INT_WS_W 11
#define TIMER_INT_WS_A 12

#define TB_H 13
#define TB_W 14
#define TB_A 15

#define RESET 16

namespace PetriNetzBandEins{

class Fehlersteuerung: public Beobachter{

public:
	~Fehlersteuerung();
	static Fehlersteuerung* getInstance();
	bool aktualisiereSignale(uint8_t port, uint8_t iq, uint8_t state);
	void execute();
	void initNetz();
private:

	static Fehlersteuerung *instance;

	//Schaltbedingungen
	uint8_t plaetze[ANZ_PLAETZE_F];
	uint8_t eingaenge[ANZ_EINGAENGE_F];

	Werkstueck *ws_h;
	Werkstueck *ws_w;
	Werkstueck *ws_a;

	Fehlersteuerung();

	void ladeWerkstueckHoehenmessung();
	void ladeWerkstueckWeiche();
	void ladeWerkstueckAuslauf();
	void schreibeSignale();
	void transitionenAusfuehren();

	void lichtschrankeEinlauf();
	void lichtschrankeHoehenmessung();
	void lichtschrankeWeiche();
	void lichtschrankeAuslauf();
	void lichtschrankeRutsche();

	void werkstueckTimerFehler(uint8_t ls, uint8_t timer_int_ws, uint8_t check, uint8_t tb);
	void lichtschrankeTimerFehler(uint8_t ls, uint8_t timer_int, uint8_t check);
	void fehlerBehandlung(uint8_t reset_2);
	bool checkToleranzbereich(int timer, int tb);


};
}
#endif
