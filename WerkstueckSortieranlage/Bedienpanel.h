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
	virtual ~Bedienpanel();
	void led_Starttaste();
	void led_Resettaste();
	void led_Q1();
	void led_Q2();
	bool taste_Start();
	bool taste_Stopp();
	bool taste_Reset();
	bool taste_EStopp();
private:
	Bedienpanel();
friend class HAL;
};

#endif /* BEDIENPANEL_H */
