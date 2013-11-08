/*
 * Ampel.h
 *
 *  Created on: 20.10.2013
 *      Author: Ruben Christian Buhl
 */

#ifndef AMPEL_H
#define AMPEL_H

#include "HAL.h"
#include "Blinker.h"

class Blinker;

class Ampel
{
public:
	virtual ~Ampel();
	void gruenBlinken(int millisekunden);
	void gelbBlinken(int millisekunden);
	void rotBlinken(int millisekunden);
	void gruen(bool ein);
	void gelb(bool ein);
	void rot(bool ein);
private:
	Ampel();
	void blinkerStopp(Blinker *blinker);
	Blinker *gruenBlinker;
	Blinker *gelbBlinker;
	Blinker *rotBlinker;
friend class HAL;
};

#endif /* AMPEL_H */
