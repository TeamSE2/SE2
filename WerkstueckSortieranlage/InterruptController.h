/**
 * @file    InterruptController.h
 * @date    03.11.2013
 * @author  Ruben Christian Buhl
 * @brief   Datei_Beschreibung_Kurz
 *
 * Datei_Beschreibung_Lang
 */

/**
 * Funktion_Beschreibung_Kurz
 *
 * @param   Parameter_Name  Parameter_Beschreibung
 * @return  Rueckgabe_Beschreibung
 *
 * Funktion_Beschreibung_Lang
 */

#ifndef INTERRUPTCONTROLLER_H
#define INTERRUPTCONTROLLER_H

#include <stdint.h>
#include <map>

#include "HAL.h"
#include "HAWThread.h"

const struct sigevent* interruptServiceRoutine(void *arg, int id);

class InterruptController: public thread::HAWThread
{
public:
	virtual ~InterruptController();
	virtual void execute(void *arg);
	virtual void shutdown();
	void stop();
private:
	InterruptController();
	void initialize();
	void outputChange(uintptr_t port, uint8_t val);
	struct sigevent event;
	int interruptID;
	int isrChannelID;
	map<uintptr_t, uint8_t> vals;
friend class HAL;
};

#endif /* INTERRUPTCONTROLLER_H */
