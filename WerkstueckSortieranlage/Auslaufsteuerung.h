#ifndef AUSLAUFSTEUERUNG_H
#define AUSLAUFSTEUERUNG_H
#include <stdint.h>
#include <stdlib.h>
#include "Werkstueck.h"
#include "HAWThread.h"
#include "Beobachter.h"
#include "SynBandEins.h"
#include "HAL.h"
#include "Dispatcher.h"

//init
#define ANZ_PLAETZE_A 6
#define ANZ_EINGAENGE_A 4
// Plaetze
#define GZ 0
#define CHECK 1
#define WENDEN_1 2
#define WENDEN_2 3
#define UEBERGABE 4
#define WARTE_A 5

// Eingangs Signale
#define METALL_A 0
#define LOCH 1
#define LICHTSCHRANKE_A 2

namespace PetriNetzBandEins{
class Auslaufsteuerung: public Beobachter {
public:
	virtual ~Auslaufsteuerung();
	static Auslaufsteuerung* getInstance();
	void aktualisiereSignale(uint8_t iq, uint8_t state);
	void execute();
private:
	Auslaufsteuerung();
	uint8_t eingang[ANZ_EINGAENGE_A];
	uint8_t plaetze[ANZ_PLAETZE_A];
	Werkstueck *temp_ws;

	static Auslaufsteuerung *instance;
	void initNetz();
	void ladeWerkstueck();
	void schreibeSignale();
	void transitionenAusfuehren();
};
}
#endif
