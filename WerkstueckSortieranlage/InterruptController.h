/**
 * @file    InterruptController.h
 * @date    03.11.2013
 * @author  Ruben Christian Buhl
 * @brief   InterruptController Header
 */

#ifndef INTERRUPTCONTROLLER_H
#define INTERRUPTCONTROLLER_H

#include <pthread.h>
#include <stdint.h>
#include <map>

#include "HAL.h"
#include "HAWThread.h"

const struct sigevent* interruptServiceRoutine(void *arg, int id);

/**
 * Der InterruptController ist fuer die Erkennung der Interrupts zustaendig.
 *
 * Diese Klasse erbt von der Klasse HAWThread und muss auch gestartet werden um zu funktionieren.
 * Hier werden die Interrupts von der Interrupt Service Routine empfangen, aufbereitet und an den Signal Channel weitergeleitet.
 */

class InterruptController: public thread::HAWThread
{
public:
	virtual ~InterruptController();
	virtual void execute(void *arg);
	virtual void shutdown();
	void stop();
	int getSignalChannelID();
private:
	InterruptController();
	void initialize(pthread_barrier_t *barrier);
	struct sigevent event;
	int interruptID;
	int isrChannelID;
	int signalChannelID;
	int signalConnectionID;
	uint16_t sival;
friend class HAL;
};

#endif /* INTERRUPTCONTROLLER_H */
