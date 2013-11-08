/*
 * Bedienpanel.cpp
 *
 *  Created on: 20.10.2013
 *      Author: Ruben Christian Buhl
 */

#include "Bedienpanel.h"

Bedienpanel::Bedienpanel()
{
}

Bedienpanel::~Bedienpanel()
{
}
void Bedienpanel::led_Starttaste(bool ein)
{
	HAL::getInstance().set(PORT_C, LED_STARTTASTE, ein);
}

void Bedienpanel::led_Resettaste(bool ein)
{
	HAL::getInstance().set(PORT_C, LED_RESETTASTE, ein);
}

void Bedienpanel::led_Q1(bool ein)
{
	HAL::getInstance().set(PORT_C, LED_Q1, ein);
}

void Bedienpanel::led_Q2(bool ein)
{
	HAL::getInstance().set(PORT_C, LED_Q2, ein);
}

bool Bedienpanel::taste_Start()
{
	return HAL::getInstance().isSet(PORT_C, TASTE_START);
}

bool Bedienpanel::taste_Stopp()
{
	return !(HAL::getInstance().isSet(PORT_C, TASTE_STOPP));
}

bool Bedienpanel::taste_Reset()
{
	return HAL::getInstance().isSet(PORT_C, TASTE_RESET);
}

bool Bedienpanel::taste_EStopp()
{
	return !(HAL::getInstance().isSet(PORT_C, TASTE_ESTOPP));
}
