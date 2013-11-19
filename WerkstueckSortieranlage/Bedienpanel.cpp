/**
 * @file    Bedienpanel.cpp
 * @date    20.10.2013
 * @author  Ruben Christian Buhl
 * @brief   Bedienpanel Implementierung
 */

#include "Bedienpanel.h"

Bedienpanel::Bedienpanel()
{
}

Bedienpanel::~Bedienpanel()
{
}

/**
 * Schaltet die Starttasten-LED ein oder aus.
 *
 * @param   ein  Wahr, wenn die LED eingeschaltet werden soll. Falsch, wenn die LED ausgeschlatet werden soll.
 *
 * Bit der Starttasten-LED auf dem entsprechenden Port wird gesetzt oder geloescht.
 */

void Bedienpanel::led_Starttaste(bool ein)
{
	HAL::getInstance().set(PORT_C, LED_STARTTASTE, ein);
}

/**
 * Schaltet die Resettasten-LED ein oder aus.
 *
 * @param   ein  Wahr, wenn die LED eingeschaltet werden soll. Falsch, wenn die LED ausgeschlatet werden soll.
 *
 * Bit der Resettasten-LED auf dem entsprechenden Port wird gesetzt oder geloescht.
 */

void Bedienpanel::led_Resettaste(bool ein)
{
	HAL::getInstance().set(PORT_C, LED_RESETTASTE, ein);
}

/**
 * Schaltet die LED Q1 ein oder aus.
 *
 * @param   ein  Wahr, wenn die LED eingeschaltet werden soll. Falsch, wenn die LED ausgeschlatet werden soll.
 *
 * Bit der LED Q1 auf dem entsprechenden Port wird gesetzt oder geloescht.
 */

void Bedienpanel::led_Q1(bool ein)
{
	HAL::getInstance().set(PORT_C, LED_Q1, ein);
}

/**
 * Schaltet die LED Q2 ein oder aus.
 *
 * @param   ein  Wahr, wenn die LED eingeschaltet werden soll. Falsch, wenn die LED ausgeschlatet werden soll.
 *
 * Bit der LED Q2 auf dem entsprechenden Port wird gesetzt oder geloescht.
 */

void Bedienpanel::led_Q2(bool ein)
{
	HAL::getInstance().set(PORT_C, LED_Q2, ein);
}

//bool Bedienpanel::taste_Start()
//{
//	return HAL::getInstance().isSet(PORT_C, TASTE_START);
//}
//
//bool Bedienpanel::taste_Stopp()
//{
//	return !(HAL::getInstance().isSet(PORT_C, TASTE_STOPP));
//}
//
//bool Bedienpanel::taste_Reset()
//{
//	return HAL::getInstance().isSet(PORT_C, TASTE_RESET);
//}
//
//bool Bedienpanel::taste_EStopp()
//{
//	return !(HAL::getInstance().isSet(PORT_C, TASTE_ESTOPP));
//}
