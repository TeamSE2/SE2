#ifndef NOTAUSSTEUERUNG_H
#define NOTAUSSTEUERUNG_H


#include <stdint.h>
#include <stdlib.h>
#include "Beobachter.h"
#include "Dispatcher.h"
#include "WerkstueckDaten.h"
#include "SynBandEins.h"
#include "HAL.h"
#include "SerielleSchnittstelle.h"

//zeiten
#define LS_UNTERBRECHUNGS_ZEIT 3 // todo: zeit ermitteln
#define LS_TOLERANZBEREICH 1 // todo: zeit ermitteln
//init
#define ANZ_PLAETZE_N 4
#define ANZ_EINGAENGE_N 7

// Plaetze
#define GZ 0
#define FEHLER_L 1
#define RESET_L1 2
#define RESET_L2 3

#define FEHLER_G 4
#define RESET_G1 5
#define RESET_G2 6


//eingaenge
#define LS_E 0
#define LS_H 1
#define LS_W 2
#define LS_A 3
#define LS_R 4
#define NOTAUS_L 5
#define RESET_L 6
#define NOTAUS_G 7
#define RESET_G 8

namespace PetriNetzBandEins{

class Notaussteuerung: public Beobachter{

public:
	~Notaussteuerung();
	static Notaussteuerung* getInstance();
	bool aktualisiereSignale(uint8_t port, uint8_t iq, uint8_t state);
	void execute();
	void initNetz();
private:

	static Notaussteuerung *instance;

	//Schaltbedingungen
	uint8_t plaetze[ANZ_PLAETZE_N];
	uint8_t eingaenge[ANZ_EINGAENGE_N];

	Notaussteuerung();

	void ladeWerkstueckHoehenmessung();
	void ladeWerkstueckWeiche();
	void ladeWerkstueckAuslauf();
	void schreibeSignale();
	void transitionenAusfuehren();
	void fehlerBehandlung(uint8_t fehler, uint8_t reset_1, uint8_t reset_2, uint8_t notaus, uint8_t reset);

};
}
#endif
