/**
 * @file    SerielleSchnittstelle.h
 * @date    20.10.2013
 * @author  Ruben Christian Buhl
 * @brief   SerielleSchnittstelle Header
 */

#ifndef SERIELLESCHNITTSTELLE_H
#define SERIELLESCHNITTSTELLE_H

#include <pthread.h>

#include "Werkstueck.h"

#define DEVICE "/dev/ser1"

/**
 * Ueber die SerielleSchnittstelle kommunizieren die beiden Fliessbandanlagen miteinander.
 *
 * Diese Klasse ist als Singleton implementiert. Daher ist das einzige Objekt nur durch getInstance() erreichbar.
 * Hier werden Methoden zur Verfuegung gestellt, um Daten ueber die SerielleSchnittstelle zu senden oder zu empfangen.
 */

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
