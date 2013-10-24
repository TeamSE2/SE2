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
	/**
	 * Default Dekonstruktor
	 */
	virtual ~Metalldetektor();
	/**
	 * Liefert Material Informationen ueber das Werkstuecks.
	 * true  = Werkstueck mit Metall.
	 * false = Werkstueck ohne Metall
	 */
	bool check();
private:
	/**
	 * Default Konstruktor
	 */
	Metalldetektor();
friend class HAL;
};

#endif /* METALLDETEKTOR_H */
