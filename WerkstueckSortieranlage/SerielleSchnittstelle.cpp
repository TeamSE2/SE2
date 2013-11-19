/**
 * @file    SerielleSchnittstelle.cpp
 * @date    20.10.2013
 * @author  Ruben Christian Buhl
 * @brief   SerielleSchnittstelle Implementierung
 */

#include <unistd.h>
#include <libc.h>

#include "SerielleSchnittstelle.h"

/**
 * SerielleSchnittstelle Konstruktor
 *
 * Mutex wird initialisiert.
 */

SerielleSchnittstelle::SerielleSchnittstelle()
{
	pthread_mutex_init(&mutex, NULL);
}

/**
 * SerielleSchnittstelle Destruktor
 *
 * Mutex wird zerstoert.
 */

SerielleSchnittstelle::~SerielleSchnittstelle()
{
	pthread_mutex_destroy(&mutex);
}

/**
 * Liefert Objekt des Singleton.
 *
 * @return  Einziges Objekt von SerielleSchnittstelle
 *
 * Singleton nach Meyers Singleton implementiert.
 */

SerielleSchnittstelle& SerielleSchnittstelle::getInstance()
{
	static SerielleSchnittstelle serielleSchnittstelle;

	return serielleSchnittstelle;
}

/**
 * Sendet die Daten zu einem Werkstueck.
 *
 * @param   werkstueck  Werkstueck Struktur, welche gesendet werden soll.
 *
 * Sendet das Werkstueck mittels sendeDaten().
 */

void SerielleSchnittstelle::sendeWerkstueck(const Werkstueck* werkstueck)
{
	sendeDaten(werkstueck, sizeof(Werkstueck));
}

/**
 * Empfaengt die Daten zu einem Werkstueck.
 *
 * @param   werkstueck  Werkstueck Struktur, in welchem das empfangene Werkstueck abgelegt werden soll.
 *
 * Empfaengt das Werkstueck mittels empfangeDaten().
 */

void SerielleSchnittstelle::empfangeWerkstueck(Werkstueck* werkstueck)
{
	empfangeDaten(werkstueck, sizeof(Werkstueck));
}

/**
 * Sendet Daten.
 *
 * @param   buf  Buffer fuer die Daten, welche gesendet werden sollen.
 * @param   nbyte  Groesse des Buffer, fuer die Daten.
 *
 * Mutex wird gesperrt.
 * SerielleSchnittstelle wird geoeffnet.
 * Daten werden gesendet.
 * 200 Millisekunden lang wird gewartet.
 * SerielleSchnittstelle wird geschlossen.
 * Mutex wird entsperrt.
 */

void SerielleSchnittstelle::sendeDaten(const void* buf, ssize_t nbyte)
{
	int fileDescriptor;

	pthread_mutex_lock(&mutex);

	fileDescriptor = open(DEVICE, O_RDWR | O_NOCTTY);

	write(fileDescriptor, buf, nbyte);

	usleep(200000);

	close(fileDescriptor);

	pthread_mutex_unlock(&mutex);
}

/**
 * Empfaengt Daten.
 *
 * @param   buf  Buffer fuer die Daten, welche empfangen werden.
 * @param   nbyte  Groesse des Buffer, fuer die Daten.
 *
 * Mutex wird gesperrt.
 * SerielleSchnittstelle wird geoeffnet.
 * Daten werden empfangen.
 * SerielleSchnittstelle wird geschlossen.
 * Mutex wird entsperrt.
 */

void SerielleSchnittstelle::empfangeDaten(void* buf, ssize_t nbyte)
{
	int fileDescriptor;

	pthread_mutex_lock(&mutex);

	fileDescriptor = open(DEVICE, O_RDWR | O_NOCTTY);

	readcond(fileDescriptor, buf, nbyte, nbyte, 1, 0);

	close(fileDescriptor);

	pthread_mutex_unlock(&mutex);
}
