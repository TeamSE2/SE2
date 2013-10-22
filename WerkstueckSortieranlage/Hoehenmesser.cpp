/*
 * Hoehenmesser.cpp
 *
 *  Created on: 20.10.2013
 *      Author: Ruben Christian Buhl
 */

#include "Hoehenmesser.h"

Hoehenmesser::Hoehenmesser()
{
}

Hoehenmesser::~Hoehenmesser()
{
}

bool Hoehenmesser::check()
{
	return HAL::getInstance().in(PORT_B) & HOEHENMESSUNG_CHECK;
}

bool Hoehenmesser::lichtschranke()
{
	return HAL::getInstance().in(PORT_B) & LICHTSCHRANKE_HOEHENMESSUNG;
}
