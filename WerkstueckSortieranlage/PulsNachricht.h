/*
 * PulsNachricht.h
 *
 *  Created on: 04.12.2013
 *      Author: Pascal
 */

#ifndef PULSNACHRICHT_H_
#define PULSNACHRICHT_H_

#include <stdint.h>
//PORTS
#define P_B 1 //Port B
#define P_C 2 //Port C
#define SYN_BAND_EINS 3 // Laufband 1 Synchronisations
#define SYN_BAND_ZWEI 4 // Laufband 2 Synchronisations
#define FEHLER 5
#define TIMER 6
// Spezielle Interrupt quellen fuer Timer
#define IQ_E (MAX_ID + 1)
#define IQ_H (MAX_ID + 2)
#define IQ_W (MAX_ID + 3)
#define IQ_A (MAX_ID + 4)
#define IQ_R (MAX_ID + 5)


typedef struct puls_nachricht{
	uint8_t port: 8;
	uint8_t state: 1;
	int iq: 23;

} PulsNachricht;

#endif /* PULSNACHRICHT_H_ */
