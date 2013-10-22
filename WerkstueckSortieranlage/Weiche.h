/*
 * Weiche.h
 *
 *  Created on: 20.10.2013
 *      Author: Ruben Christian Buhl
 */

#ifndef WEICHE_H
#define WEICHE_H

#include "HAL.h"

class Weiche
{
public:
	virtual ~Weiche();
	void auf();
	bool offen();
	bool lichtschranke();
private:
	Weiche();
friend class HAL;
};

#endif /* WEICHE_H */
