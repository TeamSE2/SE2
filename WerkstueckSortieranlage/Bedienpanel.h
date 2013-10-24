/*
 * Bedienpanel.h
 *
 *  Created on: 20.10.2013
 *      Author: Ruben Christian Buhl
 */

#ifndef BEDIENPANEL_H
#define BEDIENPANEL_H

#include "HAL.h"

class Bedienpanel
{
public:
	/**
	 * Default Dekonstruktor
	 */
	virtual ~Bedienpanel();

	/**
	 * Diese Methode steuert die Start-LED an und bewirkt einen Zustandswechsel
	 * an --> aus
	 * aus --> an
	 */
	void led_Starttaste();
	/**
	 * Diese Methode steuert die Reset-LED an und bewirkt einen Zustandswechsel
	 * an --> aus
	 * aus --> an
	 */
	void led_Resettaste();
	/**
	 * Diese Methode steuert die Q1-LED an und bewirkt einen Zustandswechsel
	 * an --> aus
	 * aus --> an
	 */
	void led_Q1();
	/**
	 * Diese Methode steuert die Q2-LED an und bewirkt einen Zustandswechsel
	 * an --> aus
	 * aus --> an
	 */
	void led_Q2();
	/**
	 * Liefert Informationen über die Starttaste.
	 * true	 = Starttaste gedrueckt
	 * false = Starttaste nicht gedrueckt
	 */
	bool taste_Start();
	/**
	 * Liefert Informationen über die Stoptaste.
	 * true	 = Stoptaste gedrueckt
	 * false = Stoptaste nicht gedrueckt
	 */
	bool taste_Stopp();
	/**
	 * Liefert Informationen über die Resettaste.
	 * true	 = Resettaste gedrueckt
	 * false = Resettaste nicht gedrueckt
	 */
	bool taste_Reset();
	/**
	 * Liefert Informationen über die E-Stoptaste.
	 * true	 = E-Stoptaste gedrueckt
	 * false = E-Stoptaste nicht gedrueckt
	 */
	bool taste_EStopp();
private:
	/**
	 * Default Konstruktor
	 */
	Bedienpanel();
friend class HAL;
};

#endif /* BEDIENPANEL_H */
