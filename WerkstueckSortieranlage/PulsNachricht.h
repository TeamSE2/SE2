/*
 * PulsNachricht.h
 *
 *  Created on: 04.12.2013
 *      Author: Pascal
 */

#ifndef PULSNACHRICHT_H_
#define PULSNACHRICHT_H_

#include <stdint.h>

#define P_B 1 //Port B
#define P_C 2 //Port C
#define SYN_BAND_EINS 3 // Laufband 1 Synchronisations

typedef struct puls_nachricht{
	uint8_t port: 8;
	uint8_t iq: 8;
	uint8_t state: 1;
} PulsNachricht;

#endif /* PULSNACHRICHT_H_ */
