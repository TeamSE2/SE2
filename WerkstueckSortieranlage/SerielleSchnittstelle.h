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
	static SerielleSchnittstelle& getInstance();
	void sendeWerkstueck(const Werkstueck* werkstueck);
	void empfangeWerkstueck(Werkstueck* werkstueck);
private:
	SerielleSchnittstelle();
	virtual ~SerielleSchnittstelle();
	void sendeDaten(const void* buf, ssize_t nbyte);
	void empfangeDaten(void* buf, ssize_t nbyte);
	pthread_mutex_t mutex;
};

#endif /* SERIELLESCHNITTSTELLE_H */
