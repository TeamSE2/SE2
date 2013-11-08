/*
 * Weiche.cpp
 *
 *  Created on: 20.10.2013
 *      Author: Ruben Christian Buhl
 */

#include "Weiche.h"

Weiche::Weiche()
{
}

Weiche::~Weiche()
{
}

void Weiche::auf(bool ein)
{
	HAL::getInstance().set(PORT_A, WEICHE_AUF, ein);
}

bool Weiche::offen()
{
	return HAL::getInstance().isSet(PORT_B, WEICHE_OFFEN);
}

bool Weiche::lichtschranke()
{
	return HAL::getInstance().isSet(PORT_B, LICHTSCHRANKE_WEICHE);
}
