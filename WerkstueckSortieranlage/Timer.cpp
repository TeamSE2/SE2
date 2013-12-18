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


Timer::Timer()
{
}

Timer::~Timer()
{
}

Timer& Timer::getInstance()
{
	static Timer timer;

	return timer;
}

void Timer::initialize()
{
	struct itimerspec itime;

//	memset(&itime, 0, sizeof(itime));
//	memset(&event, 0, sizeof(event));

	itime.it_value.tv_sec = 0;
	itime.it_value.tv_nsec = TV_NSEC;
	itime.it_interval.tv_sec = 0;
	itime.it_interval.tv_nsec = TV_NSEC;

	timerChannelID = ChannelCreate(0);

	if(timerChannelID == -1)
	{
		perror("Timer: timerChannelID ChannelCreate fehlgeschlagen");

		exit(EXIT_FAILURE);
	}

	timerConnectionID = ConnectAttach(0, 0, timerChannelID, _NTO_SIDE_CHANNEL, 0);

	if(timerConnectionID == -1)
	{
		perror("Timer: timerConnectionID ConnectAttach fehlgeschlagen");

		exit(EXIT_FAILURE);
	}

	SIGEV_PULSE_INIT(&event, timerConnectionID, SIGEV_PULSE_PRIO_INHERIT, 0, 0);

	timer_create(CLOCK_REALTIME, &event, &timerID);
	timer_settime(timerID, 0, &itime, NULL);

//	dispatcherConnectionID = ConnectAttach(0, 0, Dispatcher::getInstance().getDispatcherChannelID(), _NTO_SIDE_CHANNEL, 0);
	dispatcherConnectionID =  Dispatcher::getInstance()->getDispatcherConnectionID();
	if(dispatcherConnectionID == -1)
	{
		perror("Timer: dispatcherConnectionID ConnectAttach fehlgeschlagen");

		exit(EXIT_FAILURE);
	}

	ein = true;
}

void Timer::execute(void *arg)
{
	struct _pulse pulse;

	initialize();

	while(!isStopped())
	{
		if(MsgReceivePulse(timerChannelID, &pulse, sizeof(pulse), NULL) == -1)
		{
			if(isStopped())
			{
				break;
			}

			perror("Timer: timerChannelID MsgReceivePulse fehlgeschlagen");

			exit(EXIT_FAILURE);
		}
		else
		{
			if(ein)
			{
				for(timermap::iterator timerIterator = timer.begin(); timerIterator != timer.end(); timerIterator++)
				{
					timerIterator->second -= (TV_NSEC / 1000000);

					if(timerIterator->second <= 0)
					{
						uint16_t val = timerIterator->first;

//						MsgSendPulse(dispatcherConnectionID, SIGEV_PULSE_PRIO_INHERIT, TIMER_PULSE_CODE, val);
						sendePulsMessage(val);
						printf("Timer %d abgelaufen\n", timerIterator->first);


						stoppen(timerIterator->first);
					}
				}
			}
		}
	}
}

void Timer::sendePulsMessage(uint8_t iq){
	PulsNachricht nachricht;
	int *val = NULL;
	int code = 0;

	nachricht.port = TIMER;
	nachricht.iq = iq;
	nachricht.state = 1;
	val = (int*)(&nachricht);

	MsgSendPulse(dispatcherConnectionID, SIGEV_PULSE_PRIO_INHERIT, code, *val);
}

void Timer::shutdown()
{
}

void Timer::stop()
{
	HAWThread::stop();

	if(ConnectDetach(timerConnectionID) == -1)
	{
		perror("Timer: timerConnectionID ConnectDetach fehlgeschlagen");
	}

	if(ChannelDestroy(timerChannelID) == -1)
	{
		perror("Timer: timerChannelID ChannelDestroy fehlgeschlagen");
	}

	if(ConnectDetach(dispatcherConnectionID) == -1)
	{
		perror("Timer: dispatcherConnectionID ConnectDetach fehlgeschlagen");
	}
}

void Timer::starten(int id, long millisekunden)
{
	timer[id] = millisekunden;
}

void Timer::stoppen(int id)
{
	timer.erase(id);
}

void Timer::warten(bool warten)
{
	ein = warten;
}

long Timer::get(int id)
{
	return timer[id];
}
