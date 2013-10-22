/*
 * Ampel.h
 *
 *  Created on: 20.10.2013
 *      Author: Ruben Christian Buhl
 */

#ifndef AMPEL_H
#define AMPEL_H

#include "HAL.h"

class Ampel
{
public:
	virtual ~Ampel();
	void gruen();
	void gelb();
	void rot();
private:
	Ampel();
friend class HAL;
};

#endif /* AMPEL_H */
