/**
 * @file    Blinker.h
 * @date    05.11.2013
 * @author  Ruben Christian Buhl
 * @brief   Datei_Beschreibung_Kurz
 *
 * Datei_Beschreibung_Lang
 */

/**
 * Funktion_Beschreibung_Kurz
 *
 * @param   Parameter_Name  Parameter_Beschreibung
 * @return  Rueckgabe_Beschreibung
 *
 * Funktion_Beschreibung_Lang
 */

#ifndef BLINKER_H
#define BLINKER_H

#include <stdint.h>

#include "Ampel.h"
#include "HAWThread.h"

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
