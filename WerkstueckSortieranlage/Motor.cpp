/**
 * @file    Motor.cpp
 * @date    20.10.2013
 * @author  Ruben Christian Buhl
 * @brief   Motor Implementierung
 */

#include "Motor.h"

Motor::Motor()
{
}

Motor::~Motor()
{
}

/**
 * Schaltet den Rechtslauf des Fliessbands ein oder aus.
 *
 * @param   ein  Wahr, wenn der Rechtslauf eingeschaltet werden soll. Falsch, wenn der Rechtslauf ausgeschlatet werden soll.
 *
 * Bit des Rechtslaufs auf dem entsprechenden Port wird gesetzt oder geloescht.
 */

void Motor::rechtslauf(bool ein)
{
	HAL::getInstance().set(PORT_A, MOTOR_RECHTSLAUF, ein);
}

/**
 * Schaltet den Linkslauf des Fliessbands ein oder aus.
 *
 * @param   ein  Wahr, wenn der Linkslauf eingeschaltet werden soll. Falsch, wenn der Linkslauf ausgeschlatet werden soll.
 *
 * Bit des Linkslaufs auf dem entsprechenden Port wird gesetzt oder geloescht.
 */

void Motor::linkslauf(bool ein)
{
	HAL::getInstance().set(PORT_A, MOTOR_LINKSLAUF, ein);
}

/**
 * Schaltet den langsamen Betrieb des Fliessbands ein oder aus.
 *
 * @param   ein  Wahr, wenn das Fliessband langsam laufen soll. Falsch, wenn das Fliessband normal laufen soll.
 *
 * Bit des langsamen Laufs auf dem entsprechenden Port wird gesetzt oder geloescht.
 */

void Motor::langsam(bool ein)
{
	HAL::getInstance().set(PORT_A, MOTOR_LANGSAM, ein);
}

/**
 * Schaltet den Betrieb des Fliessbands ein oder aus.
 *
 * @param   ein  Wahr, wenn das Fliessband stoppen soll. Falsch, wenn das Fliessband betrieben werden soll.
 *
 * Bit zum Stoppen des Fliessbands auf dem entsprechenden Port wird gesetzt oder geloescht.
 */

void Motor::stopp(bool ein)
{
	HAL::getInstance().set(PORT_A, MOTOR_STOPP, ein);
}
