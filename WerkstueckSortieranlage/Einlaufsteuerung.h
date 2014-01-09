
#ifndef EINLAUFSTEUERUNG_H
#define EINLAUFSTEUERUNG_H
#include <stdint.h>
#include <stdlib.h>
#include <HAWThread.h>
#include "Beobachter.h"
#include "SynBandEins.h"
#include "Dispatcher.h"
#include "WerkstueckDaten.h"
#include "HAL.h"

//init
#define ANZ_PLAETZE_E 5
#define ANZ_EINGAENGE_E 3
#define ANZ_MARKEN_E 6
// Ausgangs Signale
#define RECHTSLAUF 1
#define KEIN_RECHTSLAUF 0
// Plaetze
#define GZ 0
#define EINLAUF 1
#define WARTE_E 2
#define MOTOR_STOP_E 3
#define VERLASSEN_E 4
//Eingaenge

namespace PetriNetzBandEins {

class Einlaufsteuerung: public Beobachter {
public:
	~Einlaufsteuerung();
	static Einlaufsteuerung* getInstance();
	bool aktualisiereSignale(uint8_t port, uint8_t iq, uint8_t state);
	void execute();
	void initNetz();
private:
	static Einlaufsteuerung *instance;
	static long werkstueck_id;
	//Schaltbedingungen
	bool lichtschranke_einlauf;
	bool timer_int;
	int timer_id;
	timespec timer;
	uint8_t eingang[ANZ_EINGAENGE_E];
	uint8_t plaetze[ANZ_PLAETZE_E];

	Einlaufsteuerung();
	void schreibeSignale();
	void transitionenAusfuehren();
	void registriereWerkstueck();
};

}

#endif
