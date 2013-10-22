/*
 * Motor.cpp
 *
 *  Created on: 20.10.2013
 *      Author: Ruben Christian Buhl
 */

#include "Motor.h"

Motor::Motor()
{
}

Motor::~Motor()
{
}

void Motor::rechtslauf()
{
	HAL::getInstance().out(PORT_A, MOTOR_RECHTSLAUF);
}

void Motor::linkslauf()
{
	HAL::getInstance().out(PORT_A, MOTOR_LINKSLAUF);
}

void Motor::langsam()
{
	HAL::getInstance().out(PORT_A, MOTOR_LANGSAM);
}

void Motor::stopp()
{
	HAL::getInstance().out(PORT_A, MOTOR_STOPP);
}
