/*
 * SerielleSchnittstelle.h
 *
 *  Created on: 20.10.2013
 *      Author: Ruben Christian Buhl
 */

#ifndef SERIELLESCHNITTSTELLE_H
#define SERIELLESCHNITTSTELLE_H

#include <pthread.h>

#include "Werkstueck.h"

#define DEVICE "/dev/ser1"

class SerielleSchnittstelle
{
public:
	/**
	 * Liefert ein singleton Object der seriellen Schnittstelle
	 */
	static SerielleSchnittstelle& getInstance();
	/**
	 * Sendet Werkstuecke ueber die serielle Schnittstelle
	 */
	void sendeWerkstueck(const Werkstueck* werkstueck);
	/**
	 * Empfaengt Werkstuecke ueber die serielle Schnittstelle
	 */
	void empfangeWerkstueck(Werkstueck* werkstueck);
private:
	/**
	 * Konstruktor
	 * Initialisiert Mutex
	 */
	SerielleSchnittstelle();
	/**
	 * Dekonstruktor
	 * Zerstoert Mutex
	 */
	virtual ~SerielleSchnittstelle();
	/**
	 * Sendet Daten ueber die serielle Schnittstelle
	 */
	void sendeDaten(const void* buf, ssize_t nbyte);
	/**
	 * Empfaengt Daten ueber die serielle Schnittstelle
	 */
	void empfangeDaten(void* buf, ssize_t nbyte);
	pthread_mutex_t mutex;
};

#endif /* SERIELLESCHNITTSTELLE_H */
