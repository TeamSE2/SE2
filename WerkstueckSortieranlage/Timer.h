/**
 * @file    Timer.h
 * @date    10.12.2013
 * @author  Ruben Christian Buhl
 * @brief   Datei_Beschreibung_Kurz
 */

#ifndef TIMER_H
#define TIMER_H

#include <map>

#include "HAWThread.h"

#define TV_NSEC 10000000

typedef map<int, long> timermap;

class Timer: public thread::HAWThread
{
public:
	static Timer& getInstance();
	virtual void execute(void *arg);
	virtual void shutdown();
	void stop();
	void starten(int id, long millisekunden);
	void stoppen(int id);
	void warten(bool warten);
	long get(int id);
private:
	Timer();
	virtual ~Timer();
	void initialize();
	void sendePulsMessage(uint8_t iq);
	struct sigevent event;
	int timerChannelID;
	int timerConnectionID;
	int dispatcherConnectionID;
	int timerID;
	bool ein;
	timermap timer;
};

#endif /* TIMER_H */
