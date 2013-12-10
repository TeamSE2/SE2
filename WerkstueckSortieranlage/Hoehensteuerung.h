

#ifndef HOEHENSTEUERUNG_H_
#define HOEHENSTEUERUNG_H_
#include <stdint.h>
#include <stdlib.h>
#include "Werkstueck.h"
#include "HAWThread.h"
#include "SynBandEins.h"
#include "HAL.h"
#include "Beobachter.h"
#include "Dispatcher.h"
//init
#define ANZ_PLAETZE_H 4
#define ANZ_EINGAENGE_H 3
// Plaetze
#define GZ 0
#define CHECK_T 1
#define CHECK_L_1 2
#define CHECK_L_2 3

// Eingangs Signale
#define LICHTSCHRANKE 0
#define HOEHE 1
#define LOCH_H 2


namespace PetriNetzBandEins {

class Hoehensteuerung: public Beobachter{
public:
	virtual ~Hoehensteuerung();
	static Hoehensteuerung* getInstance();
	void aktualisiereSignale(uint8_t iq, uint8_t state);
	void execute();
private:
	uint8_t eingang[ANZ_EINGAENGE_H-1];
	uint8_t plaetze[ANZ_PLAETZE_H-1];
	Werkstueck *temp_ws;

	static Hoehensteuerung *instance;
	Hoehensteuerung();
	void initNetz();
	void ladeWerkstueck();
	void sendeWerkstueck();
	void schreibeSignale();
	void transitionenAusfuehren();
	bool checkLoch();

};

}

#endif
