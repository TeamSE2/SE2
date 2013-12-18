/**
 * @file    Timer.cpp
 * @date    10.12.2013
 * @author  Ruben Christian Buhl
 * @brief   Datei_Beschreibung_Kurz
 */

#include <time.h>
#include <stdint.h>

#include "Timer.h"
#include "Dispatcher.h"

long Timer::new_id = 0;

timermap Timer::timer;

Timer::Timer(timespec time)
//Timer::Timer(time_t sekunden, long nanosekunden)
{
	id = new_id;

	new_id++;

	memset(&timerspec, 0, sizeof(timerspec));
	memset(&event, 0, sizeof(event));

	timerspec.it_value = time;
//	timerspec.it_value.tv_nsec = nanosekunden;
//	timerspec.it_value.tv_sec = sekunden;

	initial_timerspec = timerspec;

//	dispatcherConnectionID = ConnectAttach(0, 0, Dispatcher::getInstance().getDispatcherChannelID(), _NTO_SIDE_CHANNEL, 0);
	dispatcherConnectionID =  Dispatcher::getInstance()->getDispatcherConnectionID();
	if(dispatcherConnectionID == -1)
	{
		perror("Timer: dispatcherConnectionID ConnectAttach fehlgeschlagen");

		exit(EXIT_FAILURE);
	}

	PulsNachricht nachricht;
	int *val = NULL;

	nachricht.iq = id;
	val = (int*)(&nachricht);

	SIGEV_PULSE_INIT(&event, dispatcherConnectionID, SIGEV_PULSE_PRIO_INHERIT, TIMER_PULSE_CODE, *val);

	timer_create(CLOCK_REALTIME, &event, &timerID);

	timer_settime(timerID, 0, &timerspec, NULL);
}

Timer::~Timer()
{
	anhalten();
	/*
	if(ConnectDetach(dispatcherConnectionID) == -1)
	{
		perror("Timer: dispatcherConnectionID ConnectDetach fehlgeschlagen");
	}
	*/
}

int Timer::starten(timespec time)
//int Timer::starten(time_t sekunden, long nanosekunden)
{
	Timer* new_timer = new Timer(time);
//	Timer* new_timer = new Timer(sekunden, nanosekunden);

	timer[new_timer->getID()] = new_timer;

	return new_timer->getID();
}

void Timer::stoppen(int id)
{
	delete timer[id];

	timer.erase(id);
}

void Timer::alle_anhalten()
{
	for(timermap::iterator timerIterator = timer.begin(); timerIterator != timer.end(); timerIterator++)
	{
		timerIterator->second->anhalten();
	}
}

void Timer::alle_fortsetzen()
{
	for(timermap::iterator timerIterator = timer.begin(); timerIterator != timer.end(); timerIterator++)
	{
		timerIterator->second->fortsetzen();
	}
}

timespec Timer::gettime(int id)
{
	return timer[id]->gettime();
}

timespec Timer::getelapsedtime(int id)
{
	return timer[id]->getelapsedtime();
}

//long Timer::getNanosekunden(int id)
//{
//	return timer[id]->getNanosekunden();
//}
//
//time_t Timer::getSekunden(int id)
//{
//	return timer[id]->getSekunden();
//}

void Timer::anhalten()
{
//	timerspec.it_value.tv_nsec = getNanosekunden();
//	timerspec.it_value.tv_sec = getSekunden();
	timerspec.it_value = gettime();

	timer_delete(timerID);
}

void Timer::fortsetzen()
{
	timer_create(CLOCK_REALTIME, &event, &timerID);

	timer_settime(timerID, 0, &timerspec, NULL);
}

long Timer::getID()
{
	return id;
}

timespec Timer::gettime()
{
	timer_gettime(timerID, &timerspec);

	return timerspec.it_value;
}

timespec Timer::getelapsedtime()
{
	itimerspec elapsed_timerspec;

	timer_gettime(timerID, &elapsed_timerspec);

	elapsed_timerspec.it_value.tv_sec = initial_timerspec.it_value.tv_sec - elapsed_timerspec.it_value.tv_sec;
	elapsed_timerspec.it_value.tv_nsec = initial_timerspec.it_value.tv_nsec - elapsed_timerspec.it_value.tv_nsec;

	if(elapsed_timerspec.it_value.tv_nsec < 0)
	{
		elapsed_timerspec.it_value.tv_sec = elapsed_timerspec.it_value.tv_sec - 1;
		elapsed_timerspec.it_value.tv_nsec = elapsed_timerspec.it_value.tv_nsec + 1000000000;
	}

	return elapsed_timerspec.it_value;
}

//long Timer::getNanosekunden()
//{
//	timer_gettime(timerID, &timerspec);
//
//	return timerspec.it_value.tv_nsec;
//}
//
//time_t Timer::getSekunden()
//{
//	timer_gettime(timerID, &timerspec);
//
//	return timerspec.it_value.tv_sec;
//}
