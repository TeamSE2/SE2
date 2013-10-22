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
void Bedienpanel::led_Starttaste()
{
	HAL::getInstance().out(PORT_C, LED_STARTTASTE);
}

void Bedienpanel::led_Resettaste()
{
	HAL::getInstance().out(PORT_C, LED_RESETTASTE);
}

void Bedienpanel::led_Q1()
{
	HAL::getInstance().out(PORT_C, LED_Q1);
}

void Bedienpanel::led_Q2()
{
	HAL::getInstance().out(PORT_C, LED_Q2);
}

bool Bedienpanel::taste_Start()
{
	return HAL::getInstance().in(PORT_C) & TASTE_START;
}

bool Bedienpanel::taste_Stopp()
{
	return !(HAL::getInstance().in(PORT_C) & TASTE_STOPP);
}

bool Bedienpanel::taste_Reset()
{
	return HAL::getInstance().in(PORT_C) & TASTE_RESET;
}

bool Bedienpanel::taste_EStopp()
{
	return !(HAL::getInstance().in(PORT_C) & TASTE_ESTOPP);
}
