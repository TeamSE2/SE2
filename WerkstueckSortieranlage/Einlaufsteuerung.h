
#ifndef EINLAUFSTEUERUNG_H
#define EINLAUFSTEUERUNG_H
#include <stdint.h>
#include <stdlib.h>
#include <HAWThread.h>
#include "Beobachter.h"
#include "SynBandEins.h"
#include "Dispatcher.h"
#include "Werkstueck.h"
#include "HAL.h"
//init
#define ANZ_PLAETZE_E 3
#define ANZ_EINGABE_E 2
#define ANZ_MARKEN_E 6
// Ausgangs Signale
#define RECHTSLAUF 1
#define KEIN_RECHTSLAUF 0
// Plaetze
#define GZ 0
#define EINLAUF 1
#define WARTE_E 2

namespace PetriNetzBandEins {

class Einlaufsteuerung: public Beobachter {
public:
	~Einlaufsteuerung();
	static Einlaufsteuerung* getInstance();
	bool aktualisiereSignale(uint8_t port, uint8_t iq, uint8_t state);
	void execute();
private:
	static Einlaufsteuerung *instance;
	static long werkstueck_id;
	//Schaltbedingungen
	bool lichtschranke_einlauf;
	uint8_t plaetze[ANZ_PLAETZE_E];

	Einlaufsteuerung();
	void initNetz();
	void leseSignale();
	void schreibeSignale();
	void transitionenAusfuehren();
	void registriereWerkstueck();


};

}

#endif
