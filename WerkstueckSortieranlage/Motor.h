/*
 * Motor.h
 *
 *  Created on: 20.10.2013
 *      Author: Ruben Christian Buhl
 */

#ifndef MOTOR_H
#define MOTOR_H

#include "HAL.h"

class Motor
{
public:
	virtual ~Motor();
	void rechtslauf();
	void linkslauf();
	void langsam();
	void stopp();
private:
	Motor();
friend class HAL;
};

#endif /* MOTOR_H */
