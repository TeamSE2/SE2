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

class Timer;

typedef map<long, Timer*> timermap;

class Timer
{
public:
	static int starten(timespec time);
//	static int starten(time_t sekunden, long nanosekunden);
	static void stoppen(int id);
	static void alle_anhalten();
	static void alle_fortsetzen();
	static timespec gettime(int id);
	static timespec getelapsedtime(int id);
//	static long getNanosekunden(int id);
//	static time_t getSekunden(int id);
private:
	Timer(timespec time);
//	Timer(time_t sekunden, long nanosekunden);
	virtual ~Timer();
	void anhalten();
	void fortsetzen();
	long getID();
	timespec gettime();
	timespec getelapsedtime();
//	long getNanosekunden();
//	time_t getSekunden();
	static long new_id;
	static timermap timer;
	sigevent event;
	itimerspec initial_timerspec;
	itimerspec timerspec;
	long id;
	int timerID;
	int dispatcherConnectionID;
};

#endif /* TIMER_H */
