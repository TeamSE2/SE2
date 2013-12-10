
#ifndef DETEKTORSTEUERUNG_H_
#define DETEKTORSTEUERUNG_H_
#include <stdint.h>
#include <stdlib.h>
#include "SynBandEins.h"
#include "Werkstueck.h"
#include "HAWThread.h"
#include "Beobachter.h"
#include "HAL.h"
#include "Dispatcher.h"

//init
#define ANZ_PLAETZE 3
#define ANZ_EINGAENGE 2
// Plaetze
#define GZ 0
#define CHECK_M 1
#define WARTE 2
// Eingangs Signale
#define LICHTSCHRANKE 0
#define METALL 1

namespace PetriNetzBandEins{

class Detektorsteuerung: public Beobachter{
public:
	virtual ~Detektorsteuerung();
	static Detektorsteuerung* getInstance();
	void aktualisiereSignale(uint8_t iq, uint8_t state);
	void execute();
private:
	uint8_t eingang[ANZ_EINGAENGE-1];
	uint8_t plaetze[ANZ_PLAETZE-1];
	Werkstueck *temp_ws;

	static Detektorsteuerung *instance;
	Detektorsteuerung();
	void initNetz();
	void ladeWerkstueck();
	void schreibeSignale();
	void transitionenAusfuehren();
};

}
#endif