/*
 * Rutsche.h
 *
 *  Created on: 20.10.2013
 *      Author: Ruben Christian Buhl
 */

#ifndef RUTSCHE_H
#define RUTSCHE_H

#include "HAL.h"

class Rutsche
{
public:
	virtual ~Rutsche();
	bool voll();
private:
	Rutsche();
friend class HAL;
};

#endif /* RUTSCHE_H */
