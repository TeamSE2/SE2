/**
 * @file    SerielleSchnittstelle.cpp
 * @date    20.10.2013
 * @author  Ruben Christian Buhl
 * @brief   SerielleSchnittstelle Implementierung
 */

#include <unistd.h>
#include <libc.h>

#include "SerielleSchnittstelle.h"
#include "HAL.h"
#include "Dispatcher.h"

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

void SerielleSchnittstelle::initialize()
{
	/*
	dispatcherConnectionID = ConnectAttach(0, 0, Dispatcher::getInstance().getDispatcherChannelID(), _NTO_SIDE_CHANNEL, 0);

	if(dispatcherConnectionID == -1)
	{
		perror("SerielleSchnittstelle: dispatcherConnectionID ConnectAttach fehlgeschlagen");

		exit(EXIT_FAILURE);
	}
	*/

	dispatcherConnectionID = Dispatcher::getInstance()->getDispatcherConnectionID();
}

void SerielleSchnittstelle::execute(void *arg)
{
	Nachricht nachricht;

	initialize();

	while(!isStopped())
	{
		empfangeNachricht(&nachricht);

		switch(nachricht)
		{
			case RESET_P:
				sendePulsMessage(nachricht, 1);
				break;
			case RESET_N:
				sendePulsMessage(nachricht, 0);
				break;
			case ESTOPP_P:
				sendePulsMessage(nachricht, 1);
				break;
			case ESTOPP_N:
				sendePulsMessage(nachricht, 0);
				break;
			case WERKSTUECK:
				empfangeWerkstueckDaten(&werkstueckDaten);
				break;
			case EMPFANGS_BEREIT:
				PetriNetzBandEins::SynBandEins::getInstance()->inkrementSynUebergabeBereit();
				break;
		}
//		MsgSendPulse(dispatcherConnectionID, SIGEV_PULSE_PRIO_INHERIT, SERIAL_PULSE_CODE, nachricht);
	}
}

void SerielleSchnittstelle::shutdown()
{
}

void SerielleSchnittstelle::sendePulsMessage(uint8_t iq, uint8_t state){
	PulsNachricht nachricht;
	int *val = NULL;
	int code = state;

	nachricht.port = FEHLER;
	nachricht.iq = iq;
	nachricht.state = state;
	val = (int*)(&nachricht);

	MsgSendPulse(dispatcherConnectionID, SIGEV_PULSE_PRIO_INHERIT, code, *val);
}

void SerielleSchnittstelle::stop()
{
	HAWThread::stop();

	if(ConnectDetach(dispatcherConnectionID) == -1)
	{
		perror("SerielleSchnittstelle: dispatcherConnectionID ConnectDetach fehlgeschlagen");
	}
}

void SerielleSchnittstelle::sendeNachricht(const Nachricht nachricht)
{
	sendeDaten(&nachricht, sizeof(Nachricht));
}

void SerielleSchnittstelle::empfangeNachricht(Nachricht* nachricht)
{
	empfangeDaten(nachricht, sizeof(Nachricht));
}

/**
 * Sendet die Daten zu einem Werkstueck.
 *
 * @param   werkstueck  Werkstueck Struktur, welche gesendet werden soll.
 *
 * Sendet das Werkstueck mittels sendeDaten().
 */

void SerielleSchnittstelle::sendeWerkstueckDaten(const WerkstueckDaten* werkstueckDaten)
{
	sendeDaten(werkstueckDaten, sizeof(WerkstueckDaten));
}

/**
 * Empfaengt die Daten zu einem Werkstueck.
 *
 * @param   werkstueck  Werkstueck Struktur, in welchem das empfangene Werkstueck abgelegt werden soll.
 *
 * Empfaengt das Werkstueck mittels empfangeDaten().
 */

void SerielleSchnittstelle::empfangeWerkstueckDaten(WerkstueckDaten* werkstueckDaten)
{
	empfangeDaten(werkstueckDaten, sizeof(WerkstueckDaten));
}

WerkstueckDaten SerielleSchnittstelle::getWerkstueckDaten()
{
	return werkstueckDaten;
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

//	pthread_mutex_lock(&mutex);

	fileDescriptor = open(DEVICE, O_RDWR | O_NOCTTY);

	readcond(fileDescriptor, buf, nbyte, nbyte, 1, 0);

	close(fileDescriptor);

//	pthread_mutex_unlock(&mutex);
}
