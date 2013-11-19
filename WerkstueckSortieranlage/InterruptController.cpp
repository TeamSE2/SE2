/**
 * Diese Datei enthaelt die Implementierung der Klasse InterruptController und definiert die, fuer den Empfang der Interrupts, benoetigte Funktion.
 *
 * @file    InterruptController.cpp
 * @date    03.11.2013
 * @author  Ruben Christian Buhl
 * @brief   InterruptController Implementierung
 */

#include "InterruptController.h"
#include "HWaccess.h"

int isrConnectionID;

/**
 * Interrupt Service Routine (ISR)
 *
 * @param   arg  Speicherbereich, welcher beim Aufruf von InterruptAttach() spezifiziert wurde.
 * @param   id  ID, welche vom Aufruf von InterruptAttach() zurueckgegeben wurde.
 * @return  Event Struktur, welche als Pulse Message an den Empfaenger der ISR gesendet wird.
 *
 * Zuerst wird festgestellt ob der Interrupt fuer unseren Zweck relevant ist.
 * Dann wird der Interrupt Status Port zurueckgesetzt und anschliessend die Pulse Message initialisiert.
 * Der Code der Pulse Message enthaelt das Interrupt Status Register, auf welchem der Interrupt aufgetreten ist.
 * Der Wert der Pulse Message enthaelt den neuen Wert der Ports, welche von einem Interrupt betroffen sein koennten.
 */

const struct sigevent* interruptServiceRoutine(void *arg, int id)
{
	struct sigevent *event = (struct sigevent *) arg;

	uint8_t status = in8(INTERRUPT_STATUS) & (INTERRUPT_STATUS_PORT_B | INTERRUPT_STATUS_PORT_C);

	if(status > 0)
	{
		uint16_t val;

		out8(INTERRUPT_STATUS, 0);

		val = (in8(PORT_B) << 8) | (in8(PORT_C) & 0xF0);

		SIGEV_PULSE_INIT(event, isrConnectionID, SIGEV_PULSE_PRIO_INHERIT, status, val);
	}
	else
	{
		event = NULL;
	}

	return event;
}

InterruptController::InterruptController()
{
}

InterruptController::~InterruptController()
{
}

/**
 * Initialisiert den InterruptController.
 *
 * @param   barrier  Die Barrier, an welcher sich die Methode meldet, wenn die Initialisierung abgeschlossen ist.
 *
 * Channels und Connections fuer das Interrupt Message Passing werden erstellt.
 * Aktiviert Interrupts und bindet die Interrupts an die ISR.
 * Setzt den Interrupt Status Port zurueckt.
 * Initialisiert die Interrupt Control Register.
 * Initialisiert sival.
 * Meldet sich anschliessend an der Barrier.
 */

void InterruptController::initialize(pthread_barrier_t *barrier)
{
	isrChannelID = ChannelCreate(0);

	if(isrChannelID == -1)
	{
		perror("InterruptController: isrChannelID ChannelCreate fehlgeschlagen");

		exit(EXIT_FAILURE);
	}

	isrConnectionID = ConnectAttach(0, 0, isrChannelID, _NTO_SIDE_CHANNEL, 0);

	if(isrConnectionID == -1)
	{
		perror("InterruptController: isrConnectionID ConnectAttach fehlgeschlagen");

		exit(EXIT_FAILURE);
	}

	SIGEV_PULSE_INIT(&event, isrConnectionID, SIGEV_PULSE_PRIO_INHERIT, 0, 0);

	interruptID = InterruptAttach(INTERRUPT_REQUEST, interruptServiceRoutine, &event, sizeof(event), 0);

	if(interruptID == -1)
	{
		perror("InterruptController: interruptID InterruptAttach fehlgeschlagen");

		exit(EXIT_FAILURE);
	}

	HAL::getInstance().out(INTERRUPT_STATUS, 0);
	HAL::getInstance().out(INTERRUPT_CONTROL, HAL::getInstance().in(INTERRUPT_CONTROL) | INTERRUPT_DISABLE);
	HAL::getInstance().out(INTERRUPT_CONTROL, HAL::getInstance().in(INTERRUPT_CONTROL) & ~(INTERRUPT_CONTROL_PORT_B | INTERRUPT_CONTROL_PORT_C));

	sival = (in8(PORT_B) << 8) | (in8(PORT_C) & 0xF0);

	signalChannelID = ChannelCreate(0);

	if(signalChannelID == -1)
	{
		perror("InterruptController: signalChannelID ChannelCreate fehlgeschlagen");

		exit(EXIT_FAILURE);
	}

	signalConnectionID = ConnectAttach(0, 0, signalChannelID, _NTO_SIDE_CHANNEL, 0);

	if(signalConnectionID == -1)
	{
		perror("InterruptController: signalConnectionID ConnectAttach fehlgeschlagen");

		exit(EXIT_FAILURE);
	}

	pthread_barrier_wait(barrier);
}

/**
 * Von HAWThread geerbte Methode, welche beim Starten des Thread aufgerufen wird.
 *
 * @param   arg  Der Parameter, welcher beim Starten des Thread uebergeben wird. Enthaelt die Barrier, welche an die Methode initialize(), zur Synchronisation uebergeben wird.
 *
 * Thread wird mit dem Aufruf von initialize() initialisiert.
 * Schleife des Thread wird gestartet und laeuft bis der Thread gestoppt wird.
 * In der Schleife werden die Pulse Messages der ISR empfangen, aufbereitet und mit einer weiteren Pulse Message an den Signal Channel gesendet.
 * Der Code der neuen Pulse Message enthaelt die Information, ob der neue Wert des geaenderten Bit 1 oder 0 ist.
 * Der Wert der neuen Pulse Message enthaelt das Bit, welches sich durch einen Interrupt geaendertet hat. Dabei ist der Wert als Port B konkatiniert mit Port C zu lesen.
 */

void InterruptController::execute(void *arg)
{
	struct _pulse pulse;

	initialize((pthread_barrier_t *) arg);

	while(!isStopped())
	{
		if(MsgReceivePulse(isrChannelID, &pulse, sizeof(pulse), NULL) == -1)
		{
			if(isStopped())
			{
				break;
			}

			perror("InterruptController: isrChannelID MsgReceivePulse fehlgeschlagen");

			exit(EXIT_FAILURE);
		}
		else
		{
			uint16_t val = pulse.value.sival_int ^ sival;

			for(uint16_t i = 0x8000; i > 0; i = i >> 1)
			{
				if(val & i)
				{
					bool code = pulse.value.sival_int & i;

					MsgSendPulse(signalConnectionID, SIGEV_PULSE_PRIO_INHERIT, code, val);
				}
			}

			sival = pulse.value.sival_int;
		}
	}
}

void InterruptController::shutdown()
{
}

/**
 * Von HAWThread ueberschriebene Methode, welche zum Stoppen des Thread aufgerufen wird.
 *
 * Die entsprechende Methode von HAWThread wird aufgerufen.
 * Channels und Connections fuer das Interrupt Message Passing werden zerstoert.
 * Deaktiviert Interrupts.
 */

void InterruptController::stop()
{
	HAWThread::stop();

	if(ConnectDetach(isrConnectionID) == -1)
	{
		perror("InterruptController: isrConnectionID ConnectDetach fehlgeschlagen");
	}

	if(ChannelDestroy(isrChannelID) == -1)
	{
		perror("InterruptController: isrChannelID ChannelDestroy fehlgeschlagen");
	}

	if(ConnectDetach(signalConnectionID) == -1)
	{
		perror("InterruptController: signalConnectionID ConnectDetach fehlgeschlagen");
	}

	if(ChannelDestroy(signalChannelID) == -1)
	{
		perror("InterruptController: signalChannelID ChannelDestroy fehlgeschlagen");
	}

	#ifndef SIMULATION
		if(InterruptDetach(interruptID) == -1)
		{
			perror("InterruptController: interruptID InterruptDetach fehlgeschlagen");
		}
	#endif
}

/**
 * Stellt den Signal Channel zur Verfuegung.
 *
 * @return  Enthaelt die Signal Channel ID.
 *
 * Liefert die Signal Channel ID, mit welcher sich andere Threads fuer den Empfang der Interrupt Informationen verbinden koennen.
 */

int InterruptController::getSignalChannelID()
{
	return signalChannelID;
}
