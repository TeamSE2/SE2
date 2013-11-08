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
	void led_Starttaste(bool ein);
	void led_Resettaste(bool ein);
	void led_Q1(bool ein);
	void led_Q2(bool ein);
	bool taste_Start();
	bool taste_Stopp();
	bool taste_Reset();
	bool taste_EStopp();
private:
	Bedienpanel();
friend class HAL;
};

#endif /* BEDIENPANEL_H */
