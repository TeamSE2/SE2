#ifndef UEBERGABESTEUERUNG_H
#define UEBERGABESTEUERUNG_H

#include <stdint.h>
#include <stdlib.h>
#include "HAWThread.h"
#include "WerkstueckDaten.h"
#include "Beobachter.h"
#include "SynBandEins.h"
#include "HAL.h"
#include "Dispatcher.h"
#include "SerielleSchnittstelle.h"

//init
#define ANZ_PLAETZE_U 4
#define ANZ_MARKEN_U 4
#define ANZ_EINGAENGE_U 1
// Plaetze
#define GZ 0
#define SENDE_1 1
#define SENDE_2 2
#define WARTE_U 3
// Eingangs Signale
#define LICHTSCHRANKE 0

namespace PetriNetzBandEins{

class Uebergabesteuerung: public Beobachter{
public:
	virtual ~Uebergabesteuerung();
	static Uebergabesteuerung* getInstance();
	bool aktualisiereSignale(uint8_t port, uint8_t iq, uint8_t state);
	void execute();
	void initNetz();
private:
	static Uebergabesteuerung *instance;
	uint8_t eingang[ANZ_EINGAENGE_U];
	uint8_t plaetze[ANZ_PLAETZE_U];
	WerkstueckDaten *temp_ws;

	Uebergabesteuerung();
	void ladeWerkstueck();
	void schreibeSignale();
	void transitionenAusfuehren();
};


}
#endif
