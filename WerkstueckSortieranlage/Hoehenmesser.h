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
	/**
	 * Default Dekonstruktor
	 */
	virtual ~Hoehenmesser();
	/**
	 * Liefert Informationen ueber die Hoehe des Werkstuecks.
	 * true  = Werkstueck inerhalb des Toleranzbereich.
	 * false = Werkstueck zu klein oder zu groﬂ
	 */
	bool check();
	/**
	 * Liefert Informationen ueber die Lichtschranke der Hoehenmessung.
	 * true  = Werstueck in Hoehenmessung.
	 * false = Kein Werstueck in Hoehenmessung.
	**/
	bool lichtschranke();
private:
	/**
	 * Default Konstruktor
	 */
	Hoehenmesser();
friend class HAL;
};

#endif /* HOEHENMESSER_H */
