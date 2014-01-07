/**
 * @file    Ampel.h
 * @date    20.10.2013
 * @author  Ruben Christian Buhl
 * @brief   Ampel Header
 */

#ifndef AMPEL_H
#define AMPEL_H

#include "HAL.h"
#include "Blinker.h"

class Blinker;

/**
 * Ueber die Ampel werden die drei farbigen Lampen angesteuert.
 *
 * Hier werden Methoden zur Verfuegung gestellt, um die Ampel gruen, gelb oder rot leuchten oder blinken zu lassen.
 * Fuer das Blinken wird jeweils ein eigener Thread der Klasse Blinker beauftragt.
 */

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
	void blinker_loeschen(Blinker *blinker);
	Blinker *gruenBlinker;
	Blinker *gelbBlinker;
	Blinker *rotBlinker;
friend class HAL;
};

#endif /* AMPEL_H */
