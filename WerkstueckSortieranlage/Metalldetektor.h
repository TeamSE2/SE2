/*
 * Metalldetektor.h
 *
 *  Created on: 20.10.2013
 *      Author: Ruben Christian Buhl
 */

#ifndef METALLDETEKTOR_H
#define METALLDETEKTOR_H

#include "HAL.h"

class Metalldetektor
{
public:
	virtual ~Metalldetektor();
	bool check();
private:
	Metalldetektor();
friend class HAL;
};

#endif /* METALLDETEKTOR_H */
