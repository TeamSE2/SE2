/**
 * @file    Ampel.cpp
 * @date    20.10.2013
 * @author  Ruben Christian Buhl
 * @brief   Ampel Implementierung
 */

#include "Ampel.h"

Ampel::Ampel()
{
	gruenBlinker = new Blinker(AMPEL_GRUEN);
	gelbBlinker = new Blinker(AMPEL_GELB);
	rotBlinker = new Blinker(AMPEL_ROT);

	gruenBlinker->start(NULL);
	gelbBlinker->start(NULL);
	rotBlinker->start(NULL);
}

/**
 * Ampel Destruktor
 *
 * Alle Blinker werden, mittels blinkerStopp(), gestoppt.
 */

Ampel::~Ampel()
{
	blinker_loeschen(gruenBlinker);
	blinker_loeschen(gelbBlinker);
	blinker_loeschen(rotBlinker);
}

/**
 * Laesst die gruene Lampe blinken.
 *
 * @param   millisekunden  Die Anzahl der Millisekunden, in welcher die Lampe ein- oder ausgeschaltet sein soll.
 *
 * Blinker wird gegebenenfalls gestoppt und geloescht.
 * Neuer Blinker wird instanziiert und gestartet.
 */

void Ampel::gruenBlinken(int millisekunden)
{
	gruenBlinker->starten(millisekunden);
}

/**
 * Laesst die gelbe Lampe blinken.
 *
 * @param   millisekunden  Die Anzahl der Millisekunden, in welcher die Lampe ein- und ausgeschaltet sein soll.
 *
 * Blinker wird gegebenenfalls gestoppt und geloescht.
 * Neuer Blinker wird instanziiert und gestartet.
 */

void Ampel::gelbBlinken(int millisekunden)
{
	gelbBlinker->starten(millisekunden);
}

/**
 * Laesst die rote Lampe blinken.
 *
 * @param   millisekunden  Die Anzahl der Millisekunden, in welcher die Lampe ein- und ausgeschaltet sein soll.
 *
 * Entsprechender Blinker wird gegebenenfalls gestoppt und geloescht.
 * Neuer Blinker wird instanziiert und gestartet.
 */

void Ampel::rotBlinken(int millisekunden)
{
	rotBlinker->starten(millisekunden);
}

/**
 * Schaltet die gruene Lampe ein oder aus.
 *
 * @param   ein  Wahr, wenn die Lampe eingeschaltet werden soll. Falsch, wenn die Lampe ausgeschlatet werden soll.
 *
 * Entsprechender Blinker wird gegebenenfalls gestoppt und geloescht.
 * Bit der gruenen Lampe auf dem entsprechenden Port wird gesetzt oder geloescht.
 */

void Ampel::gruen(bool ein)
{
	gruenBlinker->stoppen();

	HAL::getInstance().set(PORT_A, AMPEL_GRUEN, ein);
}

/**
 * Schaltet die gelbe Lampe ein oder aus.
 *
 * @param   ein  Wahr, wenn die Lampe eingeschaltet werden soll. Falsch, wenn die Lampe ausgeschlatet werden soll.
 *
 * Entsprechender Blinker wird gegebenenfalls gestoppt und geloescht.
 * Bit der gelben Lampe auf dem entsprechenden Port wird gesetzt oder geloescht.
 */

void Ampel::gelb(bool ein)
{
	gelbBlinker->stoppen();

	HAL::getInstance().set(PORT_A, AMPEL_GELB, ein);
}

/**
 * Schaltet die rote Lampe ein oder aus.
 *
 * @param   ein  Wahr, wenn die Lampe eingeschaltet werden soll. Falsch, wenn die Lampe ausgeschlatet werden soll.
 *
 * Entsprechender Blinker wird gegebenenfalls gestoppt und geloescht.
 * Bit der roten Lampe auf dem entsprechenden Port wird gesetzt oder geloescht.
 */

void Ampel::rot(bool ein)
{
	rotBlinker->stoppen();

	HAL::getInstance().set(PORT_A, AMPEL_ROT, ein);
}

/**
 * Stoppt einen Blinker.
 *
 * @param   blinker  Der Blinker, welcher gestoppt werden soll.
 *
 * Der Blinker wird nur gestoppt, wenn er vorher instanziiert wurde.
 * Der Thread wird gestoppt.
 * Das Objekt wird geloescht.
 */

void Ampel::blinker_loeschen(Blinker *blinker)
{
	blinker->stop();
	blinker->join();

	delete blinker;
}
