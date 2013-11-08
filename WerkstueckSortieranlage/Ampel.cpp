/*
 * Ampel.cpp
 *
 *  Created on: 20.10.2013
 *      Author: Ruben Christian Buhl
 */

#include "Ampel.h"

Ampel::Ampel()
{
}

Ampel::~Ampel()
{
	blinkerStopp(gruenBlinker);
	blinkerStopp(gelbBlinker);
	blinkerStopp(rotBlinker);
}

void Ampel::gruenBlinken(int millisekunden)
{
	blinkerStopp(gruenBlinker);

	gruenBlinker = new Blinker(millisekunden, AMPEL_GRUEN);

	gruenBlinker->start(NULL);
}

void Ampel::gelbBlinken(int millisekunden)
{
	blinkerStopp(gelbBlinker);

	gelbBlinker = new Blinker(millisekunden, AMPEL_GELB);

	gelbBlinker->start(NULL);
}

void Ampel::rotBlinken(int millisekunden)
{
	blinkerStopp(rotBlinker);

	rotBlinker = new Blinker(millisekunden, AMPEL_ROT);

	rotBlinker->start(NULL);
}

void Ampel::gruen(bool ein)
{
	blinkerStopp(gruenBlinker);

	HAL::getInstance().set(PORT_A, AMPEL_GRUEN, ein);
}

void Ampel::gelb(bool ein)
{
	blinkerStopp(gelbBlinker);

	HAL::getInstance().set(PORT_A, AMPEL_GELB, ein);
}

void Ampel::rot(bool ein)
{
	blinkerStopp(rotBlinker);

	HAL::getInstance().set(PORT_A, AMPEL_ROT, ein);
}

void Ampel::blinkerStopp(Blinker *blinker)
{
	if(blinker != NULL)
	{
		blinker->stop();
		blinker->join();

		delete blinker;
	}
}
