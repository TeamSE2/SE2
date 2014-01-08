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

//timespec Timer::times[TIMES_LENGTH] = {{1, 612753596}, {0, 404938420}, {1, 118647801}, {0, 383941633}, {0, 470109467}, {0, 928220000}, {0, 928220000}, {0, 464110385}, {1, 856440000}, {0, 928220000}};
timespec Timer::times[TIMES_LENGTH] = {{1, 846717952}, {0, 394940108}, {1, 43659434}, {0, 392940414}, {0, 201150624}, {0, 756247000}, {0, 756247000}, {0, 378123543}, {1, 512494000}, {0, 756247000}};

long Timer::new_id = 1;

timermap Timer::timer;

bool Timer::running = true;
bool Timer::slow = false;

Timer::Timer(timespec time)
{
	id = new_id;

	new_id++;

	memset(&timerspec, 0, sizeof(timerspec));
	memset(&event, 0, sizeof(event));

	timerspec.it_value = time;

	initial_timerspec = timerspec;

//	dispatcherConnectionID = ConnectAttach(0, 0, Dispatcher::getInstance().getDispatcherChannelID(), _NTO_SIDE_CHANNEL, 0);
	dispatcherConnectionID =  HAL::getInstance().getInterruptController()->getSignalConnectionID();

	if(dispatcherConnectionID == -1)
	{
		perror("Timer: dispatcherConnectionID ConnectAttach fehlgeschlagen");

		exit(EXIT_FAILURE);
	}

	PulsNachricht nachricht;
	int *val = NULL;

	nachricht.iq = id;
	val = (int*)(&nachricht);

	SIGEV_PULSE_INIT(&event, dispatcherConnectionID, SIGEV_PULSE_PRIO_INHERIT, TIMER_PULSE_CODE, id);

	timer_create(CLOCK_REALTIME, &event, &timerID);

	timer_settime(timerID, 0, &timerspec, NULL);

	if(slow)
	{
		langsam();
	}

	if(!running)
	{
		anhalten();
	}
}

Timer::~Timer()
{
	anhalten();

	if(ConnectDetach(dispatcherConnectionID) == -1)
	{
		perror("Timer: dispatcherConnectionID ConnectDetach fehlgeschlagen");
	}
}

int Timer::starten(timespec time)
{
	Timer* new_timer = new Timer(time);

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
	if(running)
	{
		for(timermap::iterator timerIterator = timer.begin(); timerIterator != timer.end(); timerIterator++)
		{
			timerIterator->second->anhalten();
		}

		running = false;
	}
}

void Timer::alle_fortsetzen()
{
	if(!running)
	{
		for(timermap::iterator timerIterator = timer.begin(); timerIterator != timer.end(); timerIterator++)
		{
			timerIterator->second->fortsetzen();
		}

		running = true;
	}
}

void Timer::alle_langsam()
{
	if(!slow)
	{
		for(timermap::iterator timerIterator = timer.begin(); timerIterator != timer.end(); timerIterator++)
		{
			timerIterator->second->langsam();
		}

		slow = true;
	}
}

void Timer::alle_normal()
{
	if(slow)
	{
		for(timermap::iterator timerIterator = timer.begin(); timerIterator != timer.end(); timerIterator++)
		{
			timerIterator->second->normal();
		}

		slow = false;
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

void Timer::anhalten()
{
	timerspec.it_value = gettime();

	timer_delete(timerID);
}

void Timer::fortsetzen()
{
	timer_create(CLOCK_REALTIME, &event, &timerID);

	timer_settime(timerID, 0, &timerspec, NULL);
}

void Timer::langsam()
{
	timerspec.it_value = multiplizieren(gettime(), double_to_timespec(LANGSAM_MULTIPLIKATOR));

	timer_delete(timerID);

	timer_create(CLOCK_REALTIME, &event, &timerID);

	timer_settime(timerID, 0, &timerspec, NULL);
}

void Timer::normal()
{
	timerspec.it_value = dividieren(gettime(), double_to_timespec(LANGSAM_MULTIPLIKATOR));

	timer_delete(timerID);

	timer_create(CLOCK_REALTIME, &event, &timerID);

	timer_settime(timerID, 0, &timerspec, NULL);
}

long Timer::getID()
{
	return id;
}

double Timer::timespec_to_double(timespec time)
{
	return time.tv_sec + (time.tv_nsec / 1000000000.0);
}

timespec Timer::double_to_timespec(double time)
{
	timespec temp;

	long time_mikrosekunden = time * 1000000;

	temp.tv_sec = time;
	temp.tv_nsec = (time_mikrosekunden % 1000000) * 1000;

	return temp;
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

timespec Timer::addieren(timespec operand1, timespec operand2)
{
	timespec ergebnis;

	long nsec = operand1.tv_nsec + operand2.tv_nsec;

	ergebnis.tv_sec = operand1.tv_sec + operand2.tv_sec;

	if(nsec > 1000000000)
	{
		ergebnis.tv_sec = ergebnis.tv_sec + 1;

		nsec = nsec - 1000000000;
	}

	ergebnis.tv_nsec = nsec;

	return ergebnis;
}

timespec Timer::subtrahieren(timespec operand1, timespec operand2)
{
	timespec ergebnis;

	long nsec = operand1.tv_nsec - operand2.tv_nsec;

	ergebnis.tv_sec = operand1.tv_sec - operand2.tv_sec;

	if(nsec < 0)
	{
		ergebnis.tv_sec = ergebnis.tv_sec - 1;

		nsec = nsec + 1000000000;
	}

	ergebnis.tv_nsec = nsec;

	return ergebnis;
}

timespec Timer::multiplizieren(timespec operand1, timespec operand2)
{
	timespec ergebnis;

	double operand1_sekunden = operand1.tv_sec + (operand1.tv_nsec / 1000000000.0);
	double operand2_sekunden = operand2.tv_sec + (operand2.tv_nsec / 1000000000.0);
	double ergebnis_sekunden = operand1_sekunden * operand2_sekunden;

	long ergebnis_mikrosekunden = ergebnis_sekunden * 1000000;

	ergebnis.tv_sec = ergebnis_sekunden;
	ergebnis.tv_nsec = (ergebnis_mikrosekunden % 1000000) * 1000;

	return ergebnis;
}

timespec Timer::dividieren(timespec operand1, timespec operand2)
{
	timespec ergebnis;

	double operand1_mikrosekunden = (operand1.tv_sec * 1000000) + (operand1.tv_nsec / 1000.0);
	double operand2_mikrosekunden = (operand2.tv_sec * 1000000) + (operand2.tv_nsec / 1000.0);
	double ergebnis_sekunden = operand1_mikrosekunden / operand2_mikrosekunden;

	long ergebnis_mikrosekunden = ergebnis_sekunden * 1000000;

	ergebnis.tv_sec = ergebnis_sekunden;
	ergebnis.tv_nsec = (ergebnis_mikrosekunden % 1000000) * 1000;

	return ergebnis;
}
