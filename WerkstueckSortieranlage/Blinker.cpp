/**
 * @file    Blinker.cpp
 * @date    05.11.2013
 * @author  Ruben Christian Buhl
 * @brief   Blinker Implementierung
 */

#include <unistd.h>

#include "Blinker.h"
#include "HAL.h"

/**
 * Blinker Konstruktor
 *
 * @param   millisekunden  Die Anzahl der Millisekunden, in welcher die Lampe ein- oder ausgeschaltet sein soll.
 * @param   lampe  Das Bit der Lampe, welche ein- und ausgeschaltet werden soll.
 *
 * Die Anzahl der Millisekunden wird in Mikrosekunden umgewandelt.
 */

Blinker::Blinker(useconds_t millisekunden, uint8_t lampe)
{
	mikrosekunden = millisekunden * 1000;

	val = lampe;
}

Blinker::~Blinker()
{
}

/**
 * Von HAWThread geerbte Methode, welche beim Starten des Thread aufgerufen wird.
 *
 * @param   arg  Der Parameter, welcher beim Starten des Thread uebergeben wird.
 *
 * Schleife des Thread wird gestartet und laeuft bis der Thread gestoppt wird.
 * Bit der bestimmten Lampe auf dem entsprechenden Port wird gesetzt.
 * Mikrosekunden werden gewartet.
 * Bit der bestimmten Lampe auf dem entsprechenden Port wird geloescht.
 * Mikrosekunden werden gewartet.
 */

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
