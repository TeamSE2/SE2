/*
 * Hoehenmesser.h
 *
 *  Created on: 20.10.2013
 *      Author: Ruben Christian Buhl
 */

#ifndef HOEHENMESSER_H
#define HOEHENMESSER_H

#include "HAL.h"

class Hoehenmesser
{
public:
	virtual ~Hoehenmesser();
	bool check();
	bool lichtschranke();
private:
	Hoehenmesser();
friend class HAL;
};

#endif /* HOEHENMESSER_H */
