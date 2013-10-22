/*
 * Komponententest.h
 *
 *  Created on: 20.10.2013
 *      Author: Ruben Christian Buhl
 */

#ifndef KOMPONENTENTEST_H
#define KOMPONENTENTEST_H

#define SLEEP_SECONDS 3

class Komponententest
{
public:
	static void starten();
private:
	static void ampel();
	static void motor();
	static void weiche();
	static void bedienpanel();
};

#endif /* KOMPONENTENTEST_H */
