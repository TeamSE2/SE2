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
	/**
	 * Startet die Komponententest.
	 */
	static void starten();
private:
	/**
	 * Komponententest Ampel
	 */
	static void ampel();
	/**
	 * Komponententest Motor
	 */
	static void motor();
	/**
	 * Komponententest Weiche
	 */
	static void weiche();
	/**
	 * Komponententest Bedienpanel
	 */
	static void bedienpanel();
};

#endif /* KOMPONENTENTEST_H */
