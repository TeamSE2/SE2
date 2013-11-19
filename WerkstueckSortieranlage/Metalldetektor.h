/**
 * @file    Metalldetektor.h
 * @date    20.10.2013
 * @author  Ruben Christian Buhl
 * @brief   Metalldetektor Header
 */

#ifndef METALLDETEKTOR_H
#define METALLDETEKTOR_H

#include "HAL.h"

class Metalldetektor
{
public:
	virtual ~Metalldetektor();
//	bool check();
private:
	Metalldetektor();
friend class HAL;
};

#endif /* METALLDETEKTOR_H */
