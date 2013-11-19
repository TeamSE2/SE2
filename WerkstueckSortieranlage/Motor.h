/**
 * @file    Motor.h
 * @date    20.10.2013
 * @author  Ruben Christian Buhl
 * @brief   Motor Header
 */

#ifndef MOTOR_H
#define MOTOR_H

#include "HAL.h"

/**
 * Ueber den Motor wird das Fliessbands betrieben.
 *
 * Hier werden Methoden zur Verfuegung gestellt, um das Fliessband nach rechts, nach links, langsam oder normal laufen zu lassen oder zu stoppen.
 */

class Motor
{
public:
	virtual ~Motor();
	void rechtslauf(bool ein);
	void linkslauf(bool ein);
	void langsam(bool ein);
	void stopp(bool ein);
private:
	Motor();
friend class HAL;
};

#endif /* MOTOR_H */
