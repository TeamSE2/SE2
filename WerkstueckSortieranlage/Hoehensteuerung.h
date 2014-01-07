

#ifndef HOEHENSTEUERUNG_H_
#define HOEHENSTEUERUNG_H_
#include <stdint.h>
#include <stdlib.h>
#include "WerkstueckDaten.h"
#include "HAWThread.h"
#include "SynBandEins.h"
#include "HAL.h"
#include "Beobachter.h"
#include "Dispatcher.h"
//init
#define ANZ_PLAETZE_H 10
#define ANZ_EINGAENGE_H 5
// Plaetze
#define GZ 0
#define CHECK_T 1
#define CHECK_L_1 2
#define CHECK_L_2 3

// Eingangs Signale
#define LICHTSCHRANKE 0
#define HOEHE 1
#define LOCH_H 2

//Analog IO
#define AIO_BASE 0x320
#define START_AD  0x10
#define AIO_PORT_A (AIO_BASE + 0x02)

//Werkstueck
#define HOEHE_NORMAL 0
#define HOEHE_LOCH 1

namespace PetriNetzBandEins {

class Hoehensteuerung: public Beobachter{
public:
	virtual ~Hoehensteuerung();
	static Hoehensteuerung* getInstance();
	bool aktualisiereSignale(uint8_t port, uint8_t iq, uint8_t state);
	void execute();
	void initNetz();
private:
	uint8_t eingang[ANZ_EINGAENGE_H];
	uint8_t plaetze[ANZ_PLAETZE_H];
	WerkstueckDaten *temp_ws;

	static Hoehensteuerung *instance;
	Hoehensteuerung();
	void ladeWerkstueck();
	void sendeWerkstueck();
	void schreibeSignale();
	void transitionenAusfuehren();
	bool checkLoch();
	int leseHoehe();

};

}

#endif
