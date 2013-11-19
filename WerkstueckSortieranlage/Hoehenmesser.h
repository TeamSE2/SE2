/**
 * @file    Hoehenmesser.h
 * @date    20.10.2013
 * @author  Ruben Christian Buhl
 * @brief   Hoehenmesser Header
 */

#ifndef HOEHENMESSER_H
#define HOEHENMESSER_H

#include "HAL.h"

class Hoehenmesser
{
public:
	virtual ~Hoehenmesser();
//	bool check();
//	bool lichtschranke();
private:
	Hoehenmesser();
friend class HAL;
};

#endif /* HOEHENMESSER_H */
