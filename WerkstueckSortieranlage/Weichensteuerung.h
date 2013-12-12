/*
 * WeichenSteuerung.h
 *
 *  Created on: 24.11.2013
 *      Author: Pascal
 */

#ifndef WEICHENSTEUERUNG_H_
#define WEICHENSTEUERUNG_H_

#include <stdint.h>
#include <stdlib.h>
#include "Werkstueck.h"
#include "HAWThread.h"
#include "SynBandEins.h"
#include "HAL.h"
#include "Beobachter.h"
#include "Dispatcher.h"

//init
#define ANZ_MARKEN_W 3
#define ANZ_PLAETZE_W 8
#define ANZ_EINGAENGE_W 3
// Plaetze
#define GZ 0
#define CHECK 1
#define TB_1 2
#define TB_2 3
#define FLANKE_P 4
#define FLANKE_N 5
#define SYN_FLANKE 6
#define CHECK_R 7
// Eingangs Signale
#define LICHTSCHRANKE 0
#define HOEHE 1
#define RUTSCHE 2

namespace PetriNetzBandEins {

class Weichensteuerung: public Beobachter{
public:
	virtual ~Weichensteuerung();
	static Weichensteuerung* getInstance();
	bool aktualisiereSignale(uint8_t port, uint8_t iq, uint8_t state);
	void execute();
private:
	uint8_t eingang[ANZ_EINGAENGE_W];
	uint8_t plaetze[ANZ_PLAETZE_W];
	Werkstueck *temp_ws;

	static Weichensteuerung *instance;
	Weichensteuerung();
	void initNetz();
	void ladeWerkstueck();
	void sendeWerkstueck();
	void schreibeSignale();
	void transitionenAusfuehren();
};

}

#endif /* WEICHENSTEUERUNG_H_ */
