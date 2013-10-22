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
}

void Ampel::gruen()
{
	HAL::getInstance().out(PORT_A, AMPEL_GRUEN);
}

void Ampel::gelb()
{
	HAL::getInstance().out(PORT_A, AMPEL_GELB);
}

void Ampel::rot()
{
	HAL::getInstance().out(PORT_A, AMPEL_ROT);
}
