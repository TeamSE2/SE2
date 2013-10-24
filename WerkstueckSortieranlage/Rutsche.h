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
	/**
	 * Default Dekonstruktor
	 */
	virtual ~Rutsche();
	/**
	 * Liefert Informationen ueber die Rutsche.
	 * true  = Rutsche ist nicht voll.
	 * false = Rutsche ist voll.
	 */
	bool voll();
private:
	/**
	 * Default Konstruktor
	 */
	Rutsche();
friend class HAL;
};

#endif /* RUTSCHE_H */
