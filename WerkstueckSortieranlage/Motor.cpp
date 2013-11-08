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

void Motor::rechtslauf(bool ein)
{
	HAL::getInstance().set(PORT_A, MOTOR_RECHTSLAUF, ein);
}

void Motor::linkslauf(bool ein)
{
	HAL::getInstance().set(PORT_A, MOTOR_LINKSLAUF, ein);
}

void Motor::langsam(bool ein)
{
	HAL::getInstance().set(PORT_A, MOTOR_LANGSAM, ein);
}

void Motor::stopp(bool ein)
{
	HAL::getInstance().set(PORT_A, MOTOR_STOPP, ein);
}
