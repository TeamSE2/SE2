/*
 * HAL.cpp
 *
 *  Created on: 19.10.2013
 *      Author: Ruben Christian Buhl
 */

#include "HAL.h"
#include "HWaccess.h"

HAL::HAL()
{
	pthread_mutex_init(&(mutexe[PORT_A]), NULL);
	pthread_mutex_init(&(mutexe[PORT_B]), NULL);
	pthread_mutex_init(&(mutexe[PORT_C]), NULL);

	out8(CONTROL, CONTROL_INITIALIZER);

	interruptController = new InterruptController();
	bedienpanel = new Bedienpanel();
	ampel = new Ampel();
	motor = new Motor();
	weiche = new Weiche();
	hoehenmesser = new Hoehenmesser();
	metalldetektor = new Metalldetektor();
	rutsche = new Rutsche();
}

HAL::~HAL()
{
	delete interruptController;
	delete bedienpanel;
	delete ampel;
	delete motor;
	delete weiche;
	delete hoehenmesser;
	delete metalldetektor;
	delete rutsche;

	for(mutexmap::iterator mutexeIterator = mutexe.begin(); mutexeIterator != mutexe.end(); mutexeIterator++)
	{
		pthread_mutex_destroy(&(mutexeIterator->second));
	}
}

HAL& HAL::getInstance()
{
	static HAL hal;

	return hal;
}

void HAL::set(uintptr_t port, uint8_t val, bool on)
{
	if(isSet(port, val) != on)
	{
		toggle(port, val);
	}
}

bool HAL::isSet(uintptr_t port, uint8_t val)
{
	return in(port) & val;
}

bool HAL::lichtschrankeEinlauf()
{
	return isSet(PORT_B, LICHTSCHRANKE_EINLAUF);
}

bool HAL::lichtschrankeAuslauf()
{
	return isSet(PORT_B, LICHTSCHRANKE_AUSLAUF);
}

void HAL::toggle(uintptr_t port, uint8_t val)
{
	out(port, in8(port) ^ val);
}

void HAL::out(uintptr_t port, uint8_t val)
{
	pthread_mutex_lock(&(mutexe[port]));

	out8(port, val);

	pthread_mutex_unlock(&(mutexe[port]));
}

uint8_t HAL::in(uintptr_t port)
{
	uint8_t val;

	pthread_mutex_lock(&(mutexe[port]));

	val = in8(port);

	pthread_mutex_unlock(&(mutexe[port]));

	return val;
}

InterruptController* HAL::getInterruptController()
{
	return interruptController;
}

Bedienpanel* HAL::getBedienpanel()
{
	return bedienpanel;
}

Ampel* HAL::getAmpel()
{
	return ampel;
}

Motor* HAL::getMotor()
{
	return motor;
}

Weiche* HAL::getWeiche()
{
	return weiche;
}

Hoehenmesser* HAL::getHoehenmesser()
{
	return hoehenmesser;
}

Metalldetektor* HAL::getMetalldetektor()
{
	return metalldetektor;
}

Rutsche* HAL::getRutsche()
{
	return rutsche;
}
