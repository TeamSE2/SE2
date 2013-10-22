/*
 * Rutsche.cpp
 *
 *  Created on: 20.10.2013
 *      Author: Ruben Christian Buhl
 */

#include "Rutsche.h"

Rutsche::Rutsche()
{
}

Rutsche::~Rutsche()
{
}

bool Rutsche::voll()
{
	return !(HAL::getInstance().in(PORT_B) & RUTSCHE_VOLL);
}
