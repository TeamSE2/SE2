/*
 * Ampel.h
 *
 *  Created on: 20.10.2013
 *      Author: Ruben Christian Buhl
 */

#ifndef AMPEL_H
#define AMPEL_H

#include "HAL.h"
/**
 *
 */
class Ampel
{
public:
	/**
	 * Default Dekonstruktor
	 */
	virtual ~Ampel();
	/**
	 * Diese Methode steuert die gruene Signallampe an und bewirkt einen Zustandswechsel:
	 *  an --> aus
	 *  aus --> an
	 */
	void gruen();
	/**
	 * Diese Methode steuert die gelbe Signallampe an und bewirkt einen Zustandswechsel:
	 *  an --> aus
	 *  aus -> an
	 */
	void gelb();
	/**
	 * Diese Methode steuert die rote Signallampe an und bewirkt einen Zustandswechsel:
	 *  an --> aus
	 *  aus --> an
	 */
	void rot();
private:
	/**
	 * Default Konstruktor
	 */
	Ampel();
friend class HAL;
};

#endif /* AMPEL_H */
