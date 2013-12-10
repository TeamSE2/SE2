/**
 * @file    Weiche.h
 * @date    20.10.2013
 * @author  Ruben Christian Buhl
 * @brief   Weiche Header
 */

#ifndef WEICHE_H
#define WEICHE_H

#include "HAL.h"

/**
 * Ansteuerung der Weiche.
 *
 * Hier wird die Methode zur Verfuegung gestellt, um die Weiche zu oeffnen.
 */

class Weiche {
public:
	virtual ~Weiche();
	void auf(bool ein);
	//	bool offen();
	//	bool lichtschranke();
private:
	Weiche();
	friend class HAL;
};

#endif /* WEICHE_H */
