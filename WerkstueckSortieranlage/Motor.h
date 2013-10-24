/*
 * Motor.h
 *
 *  Created on: 20.10.2013
 *      Author: Ruben Christian Buhl
 */

#ifndef MOTOR_H
#define MOTOR_H

#include "HAL.h"

class Motor
{
public:
	/**
	 * Default Dekonstruktor
	 */
	virtual ~Motor();
	/**
	 * Diese Methode steuert den Motor an und bewirkt einen Zustandswechsel:
	 *  kein Rechtslauf --> Rechtslauf.
	 *  Rechtslauf --> kein Rechtslauf.
	 */
	void rechtslauf();
	/**
	 * Diese Methode steuert den Motor an und bewirkt einen Zustandswechsel:
	 *  kein Linkslauf --> Linkslauf.
	 *  Linkslauf --> kein Linkslauf.
	 */
	void linkslauf();
	/**
	 * Diese Methode steuert den Motor an und bewirkt einen Zustandswechsel:
	 *  Motor laeuft Langsam. --> Motor laeuft normal schnell.
	 *  Motor laeuft normal schnell. --> Motor laeuft Langsam.
	 */
	void langsam();
	/**
	 * Diese Methode steuert den Motor an und bewirkt einen Zustandswechsel:
	 *  Motor stoppt. --> Motor laeuft.
	 *  Motor laeuft. --> Motor stoppt.
	 */
	void stopp();
private:
	/**
	 * Default Konstruktor
	 */
	Motor();
friend class HAL;
};

#endif /* MOTOR_H */
