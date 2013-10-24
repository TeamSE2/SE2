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
	/**
	 * Default Dekonstruktor
	 */
	virtual ~Weiche();
	/**
	 * Diese Methode steuert die Weiche an und bewirkt einen Zustandswechsel:
	 *  zu --> auf
	 *  auf --> zu
	 */
	void auf();
	/**
	 * Liefert Informationen ueber den Zustand der Weiche.
	 * true  = Weiche offen.
	 * false = Weiche geschlossen.
	 */
	bool offen();
	/**
	 * Liefert Informationen ueber die Lichtschranke bei der Weiche.
	 * true  = Werstueck ist in Weiche.
	 * false = Kein Werstueck in Weiche.
	**/
	bool lichtschranke();
private:
	/**
	 * Default Konstruktor
	 */
	Weiche();
friend class HAL;
};

#endif /* WEICHE_H */
