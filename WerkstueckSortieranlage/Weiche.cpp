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

void Weiche::auf()
{
	HAL::getInstance().out(PORT_A, WEICHE_AUF);
}

bool Weiche::offen()
{
	return HAL::getInstance().in(PORT_B) & WEICHE_OFFEN;
}

bool Weiche::lichtschranke()
{
	return HAL::getInstance().in(PORT_B) & LICHTSCHRANKE_WEICHE;
}
