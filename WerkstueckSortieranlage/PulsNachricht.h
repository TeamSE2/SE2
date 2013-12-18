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

#define INTERRUPT1_PULSE_CODE _PULSE_CODE_MINAVAIL
#define INTERRUPT0_PULSE_CODE (_PULSE_CODE_MINAVAIL + 1)
#define SERIAL_PULSE_CODE (_PULSE_CODE_MINAVAIL + 2)
#define TIMER_PULSE_CODE (_PULSE_CODE_MINAVAIL + 3)
#define P_B (_PULSE_CODE_MINAVAIL + 4) //Port B
#define P_C (_PULSE_CODE_MINAVAIL + 5)//Port C
#define SYN_BAND_EINS (_PULSE_CODE_MINAVAIL + 6) // Laufband 1 Synchronisations
#define SYN_BAND_ZWEI (_PULSE_CODE_MINAVAIL + 7) // Laufband 2 Synchronisations
#define FEHLER (_PULSE_CODE_MINAVAIL + 8)

typedef struct puls_nachricht{
	uint32_t iq: 31;
	uint8_t state: 1;
} PulsNachricht;

#endif /* PULSNACHRICHT_H_ */
