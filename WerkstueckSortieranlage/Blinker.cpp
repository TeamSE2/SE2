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

Blinker::Blinker(uint8_t lampe)
{
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);

	val = lampe;

	ein = false;
}

Blinker::~Blinker()
{
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
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
		wait();

		HAL::getInstance().set(PORT_A, val, true);

		usleep(mikrosekunden);

		wait();

		HAL::getInstance().set(PORT_A, val, false);

		usleep(mikrosekunden);
	}
}

void Blinker::shutdown()
{
}

void Blinker::wait()
{
	pthread_mutex_lock(&mutex);

	while(!ein)
	{
		pthread_cond_wait(&cond, &mutex);
	}

	pthread_mutex_unlock(&mutex);
}

void Blinker::starten(useconds_t millisekunden)
{
	pthread_mutex_lock(&mutex);

	mikrosekunden = millisekunden * 1000;

	ein = true;

	pthread_cond_signal(&cond);

	pthread_mutex_unlock(&mutex);
}

void Blinker::stoppen()
{
	pthread_mutex_lock(&mutex);

	mikrosekunden = 0;

	ein = false;

	pthread_cond_signal(&cond);

	pthread_mutex_unlock(&mutex);
}
