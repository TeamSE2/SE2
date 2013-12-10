#ifndef UEBERGABESTEUERUNG_H
#define UEBERGABESTEUERUNG_H

#include <stdint.h>
#include <stdlib.h>
#include "HAWThread.h"
#include "Werkstueck.h"
#include "Beobachter.h"
#include "SynBandEins.h"
#include "HAL.h"
#include "Dispatcher.h"

//init
#define ANZ_PLAETZE_U 3
#define ANZ_EINGAENGE_U 2
// Plaetze
#define GZ 0
#define LESE 1
#define WARTE_U 8
// Eingangs Signale
#define LICHTSCHRANKE 0
#define READY 1

namespace PetriNetzBandEins{

class Uebergabesteuerung: public Beobachter{
public:
	virtual ~Uebergabesteuerung();
	static Uebergabesteuerung* getInstance();
	void aktualisiereSignale(uint8_t iq, uint8_t state);
	void execute();
private:
	static Uebergabesteuerung *instance;
	uint8_t eingang[ANZ_EINGAENGE_U-1];
	uint8_t plaetze[ANZ_PLAETZE_U-1];
	Werkstueck *temp_ws;

	Uebergabesteuerung();
	void initNetz();
	void ladeWerkstueck();
	void schreibeSignale();
	void transitionenAusfuehren();
};


}
#endif
