/*
 * Metalldetektor.cpp
 *
 *  Created on: 20.10.2013
 *      Author: Ruben Christian Buhl
 */

#include "Metalldetektor.h"

Metalldetektor::Metalldetektor()
{
}

Metalldetektor::~Metalldetektor()
{
}

bool check()
{
	return HAL::getInstance().in(PORT_B) & METALLDETEKTOR_CHECK;
}
