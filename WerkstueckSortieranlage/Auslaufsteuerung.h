#ifndef AUSLAUFSTEUERUNG_H
#define AUSLAUFSTEUERUNG_H
#include <stdint.h>
#include <stdlib.h>
#include "WerkstueckDaten.h"
#include "HAWThread.h"
#include "Beobachter.h"
#include "SynBandEins.h"
#include "HAL.h"
#include "Dispatcher.h"

//init
#define ANZ_PLAETZE_A 7
#define ANZ_EINGAENGE_A 5
// Plaetze
#define GZ 0
#define CHECK_1 1
#define CHECK_2 2
#define WENDEN_1 3
#define WENDEN_2 4
#define UEBERGABE 5
#define WARTE_A 6

// Eingangs Signale
#define METALL_A 0
#define LOCH 1
#define LICHTSCHRANKE_A 2
#define LICHTSCHRANKE_W 3
#define TIMER_INT 4

namespace PetriNetzBandEins{
class Auslaufsteuerung: public Beobachter {
public:
	virtual ~Auslaufsteuerung();
	static Auslaufsteuerung* getInstance();
	bool aktualisiereSignale(uint8_t port, uint8_t iq, uint8_t state);
	void execute();
	void initNetz();
private:
	Auslaufsteuerung();
	uint8_t eingang[ANZ_EINGAENGE_A];
	uint8_t plaetze[ANZ_PLAETZE_A];
	WerkstueckDaten *temp_ws;
	timespec timer;
	int timer_id;
	static Auslaufsteuerung *instance;

	void ladeWerkstueck();
	void schreibeSignale();
	void transitionenAusfuehren();
};
}
#endif
