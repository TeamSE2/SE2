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

//#define LANGSAM_MULTIPLIKATOR 3.44381
#define LANGSAM_MULTIPLIKATOR 2.51336

#define EINLAUF_BIS_HOEHENMESSUNG_INDEX 0
#define HOEHENMESSUNG_BIS_WEICHE_INDEX 1
#define WEICHE_BIS_AUSLAUF_INDEX 2
#define WEICHE_BIS_HOEHENMESSUNG_INDEX 3
#define IN_RUTSCHE_INDEX 4
#define IM_AUSLAUF_INDEX 5
#define IM_EINLAUF_INDEX 6
#define IN_WEICHE_INDEX 7
#define ABSTAND_ZWISCHEN_WERKSTUECKEN_INDEX 8
#define TOLERANZ_INDEX 9

#define TIMES_LENGTH 10

class Timer;

typedef map<long, Timer*> timermap;

class Timer
{
public:
	static int starten(timespec time);
	static void stoppen(int id);
	static void alle_anhalten();
	static void alle_fortsetzen();
	static void alle_langsam();
	static void alle_normal();
	static double timespec_to_double(timespec time);
	static timespec double_to_timespec(double time);
	static timespec gettime(int id);
	static timespec getelapsedtime(int id);
	static timespec addieren(timespec operand1, timespec operand2);
	static timespec subtrahieren(timespec operand1, timespec operand2);
	static timespec multiplizieren(timespec operand1, timespec operand2);
	static timespec dividieren(timespec operand1, timespec operand2);
	static timespec times[TIMES_LENGTH];
private:
	Timer(timespec time);
	virtual ~Timer();
	void anhalten();
	void fortsetzen();
	void langsam();
	void normal();
	long getID();
	timespec gettime();
	timespec getelapsedtime();
	static long new_id;
	static timermap timer;
	static bool running;
	static bool slow;
	sigevent event;
	itimerspec initial_timerspec;
	itimerspec timerspec;
	long id;
	int timerID;
	int dispatcherConnectionID;
};

#endif /* TIMER_H */
