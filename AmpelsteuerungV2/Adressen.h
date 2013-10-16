/*
 * Adressen.h
 */

#ifndef ADDRESSES_H_
#define ADDRESSES_H_

#define DIO_BASE 0x300          	// Basis Adresse
#define PORT_A (DIO_BASE + 0x00)    // Port A
#define PORT_B (DIO_BASE + 0x01)    // Port B
#define PORT_C (DIO_BASE + 0x02)    // Port C
#define PORT_CTRL (DIO_BASE + 0x03) // Control registet

// BIT_X wird auf ein gesetzt
#define BIT_0 0x01
#define BIT_1 0x02
#define BIT_2 0x04
#define BIT_3 0x08
#define BIT_4 0x10
#define BIT_5 0x20
#define BIT_6 0x40
#define BIT_7 0x80

//PORT_A
#define MOTOR_STOP BIT_3
#define MOTOR_RECHTS  BIT_0
#define MOTOR_LINKS  BIT_1
#define MOTOR_LANGSAM BIT_2
#define WEICHE_AUF BIT_4


#endif /* ADRESSEN_H_ */
