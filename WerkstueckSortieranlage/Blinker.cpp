/**
 * @file    Blinker.cpp
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

#include <unistd.h>

#include "Blinker.h"
#include "HAL.h"

Blinker::Blinker(useconds_t millisekunden, uint8_t lampe)
{
	mikrosekunden = millisekunden * 1000;

	val = lampe;
}

Blinker::~Blinker()
{
}

void Blinker::execute(void *arg)
{
	while(!isStopped())
	{
		HAL::getInstance().set(PORT_A, val, true);

		usleep(mikrosekunden);

		HAL::getInstance().set(PORT_A, val, false);

		usleep(mikrosekunden);
	}
}

void Blinker::shutdown()
{
}
