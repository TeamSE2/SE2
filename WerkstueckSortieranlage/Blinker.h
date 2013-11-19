/**
 * @file    Blinker.h
 * @date    05.11.2013
 * @author  Ruben Christian Buhl
 * @brief   Blinker Header
 */

#ifndef BLINKER_H
#define BLINKER_H

#include <stdint.h>

#include "Ampel.h"
#include "HAWThread.h"

/**
 * Ein Blinker wird von der Ampel gestartet, um eine bestimmte Lampe blinken zu lassen.
 *
 * Diese Klasse erbt von der Klasse HAWThread und muss auch gestartet werden um zu funktionieren.
 * Hier wird eine bestimmte Lampe immer wieder ein- und ausgeschaltet, bis der Thread gestoppt wird.
 */

class Blinker: public thread::HAWThread
{
public:
	virtual ~Blinker();
	virtual void execute(void *arg);
	virtual void shutdown();
private:
	Blinker(useconds_t millisekunden, uint8_t lampe);
	useconds_t mikrosekunden;
	uint8_t val;
friend class Ampel;
};

#endif /* BLINKER_H */
