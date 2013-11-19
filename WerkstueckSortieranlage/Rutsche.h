/**
 * @file    Rutsche.h
 * @date    20.10.2013
 * @author  Ruben Christian Buhl
 * @brief   Rutsche Header
 */

#ifndef RUTSCHE_H
#define RUTSCHE_H

#include "HAL.h"

class Rutsche
{
public:
	virtual ~Rutsche();
//	bool voll();
private:
	Rutsche();
friend class HAL;
};

#endif /* RUTSCHE_H */
