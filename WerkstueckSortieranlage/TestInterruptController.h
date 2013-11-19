/**
 * @file    TestInterruptController.h
 * @date    06.11.2013
 * @author  Ruben Christian Buhl
 * @brief   TestInterruptController Header
 */

#ifndef TESTINTERRUPTCONTROLLER_H
#define TESTINTERRUPTCONTROLLER_H

#include "HAWThread.h"

#define KOMMANDO_TEST_BEENDEN "beenden"

/**
 * Klasse zum Testen des InterruptController.
 *
 * Mit der statischen Methode starten() wird der Test der Sensoren des HAL gestartet.
 */

class TestInterruptController: public thread::HAWThread
{
public:
	static void starten(bool automatik, unsigned int sekunden);
	virtual void execute(void *arg);
	virtual void shutdown();
private:
	void ausgeben(bool code, int val);
	void initialize();
	int signalChannelID;
};

#endif /* TESTINTERRUPTCONTROLLER_H */
