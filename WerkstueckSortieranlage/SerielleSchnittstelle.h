/**
 * @file    SerielleSchnittstelle.h
 * @date    20.10.2013
 * @author  Ruben Christian Buhl
 * @brief   SerielleSchnittstelle Header
 */

#ifndef SERIELLESCHNITTSTELLE_H
#define SERIELLESCHNITTSTELLE_H

#include <pthread.h>

#include "HAWThread.h"
#include "WerkstueckDaten.h"
#include "SynBandEins.h"

#define DEVICE "/dev/ser1"

enum Nachricht
{
	RESET_P,
	RESET_N,
	ESTOPP_P,
	ESTOPP_N,
	WERKSTUECK,
	EMPFANGS_BEREIT,
	EMPFANGS_BESTAETIGUNG
};

/**
 * Ueber die SerielleSchnittstelle kommunizieren die beiden Fliessbandanlagen miteinander.
 *
 * Diese Klasse ist als Singleton implementiert. Daher ist das einzige Objekt nur durch getInstance() erreichbar.
 * Hier werden Methoden zur Verfuegung gestellt, um Daten ueber die SerielleSchnittstelle zu senden oder zu empfangen.
 */

class SerielleSchnittstelle: public thread::HAWThread
{
public:
	static SerielleSchnittstelle& getInstance();
	virtual void execute(void *arg);
	virtual void shutdown();
	void stop();
	void sendeNachricht(const Nachricht nachricht);
	void empfangeNachricht(Nachricht* nachricht);
	void sendeWerkstueckDaten(const WerkstueckDaten* werkstueckDaten);
	void empfangeWerkstueckDaten(WerkstueckDaten* werkstueckDaten);
	WerkstueckDaten getWerkstueckDaten();
private:
	SerielleSchnittstelle();
	virtual ~SerielleSchnittstelle();
	void initialize();
	void sendeDaten(const void* buf, ssize_t nbyte);
	void empfangeDaten(void* buf, ssize_t nbyte);
	void sendePulsMessage(uint8_t iq, uint8_t state);
	int dispatcherConnectionID;
	pthread_mutex_t mutex;
	WerkstueckDaten werkstueckDaten;
};

#endif /* SERIELLESCHNITTSTELLE_H */
