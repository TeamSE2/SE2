/*
 * HAL.h
 *
 *  Created on: 19.10.2013
 *      Author: Ruben Christian Buhl
 */

#ifndef HAL_H
#define HAL_H

#include <pthread.h>
#include <stdint.h>
#include <map>

#include "InterruptController.h"
#include "Bedienpanel.h"
#include "Ampel.h"
#include "Motor.h"
#include "Weiche.h"
#include "Hoehenmesser.h"
#include "Metalldetektor.h"
#include "Rutsche.h"

#define BASE 0x300
#define PORT_A (BASE + 0x00)
#define PORT_B (BASE + 0x01)
#define PORT_C (BASE + 0x02)
#define CONTROL (BASE + 0x03)
#define INTERRUPT_STATUS (BASE + 0x0F)
#define INTERRUPT_CONTROL (BASE + 0x0B)

#define CONTROL_INITIALIZER 0x8A
#define INTERRUPT_REQUEST 0x0B
#define INTERRUPT_DISABLE 0x3F
#define INTERRUPT_STATUS_PORT_B 0x02
#define INTERRUPT_STATUS_PORT_C 0x08
#define INTERRUPT_CONTROL_PORT_B 0x02
#define INTERRUPT_CONTROL_PORT_C 0x04

#define MOTOR_RECHTSLAUF 0x01
#define MOTOR_LINKSLAUF 0x02
#define MOTOR_LANGSAM 0x04
#define MOTOR_STOPP 0x08
#define WEICHE_AUF 0x10
#define AMPEL_GRUEN 0x20
#define AMPEL_GELB 0x40
#define AMPEL_ROT 0x80

#define LICHTSCHRANKE_EINLAUF 0x01
#define LICHTSCHRANKE_HOEHENMESSUNG 0x02
#define HOEHENMESSUNG_CHECK 0x04
#define LICHTSCHRANKE_WEICHE 0x08
#define METALLDETEKTOR_CHECK 0x10
#define WEICHE_OFFEN 0x20
#define RUTSCHE_VOLL 0x40
#define LICHTSCHRANKE_AUSLAUF 0x80

#define LED_STARTTASTE 0x01
#define LED_RESETTASTE 0x02
#define LED_Q1 0x04
#define LED_Q2 0x08
#define TASTE_START 0x10
#define TASTE_STOPP 0x20
#define TASTE_RESET 0x40
#define TASTE_ESTOPP 0x80

using namespace std;

typedef map<uintptr_t, pthread_mutex_t> mutexmap;

class InterruptController;
class Bedienpanel;
class Ampel;
class Motor;
class Weiche;
class Hoehenmesser;
class Metalldetektor;
class Rutsche;

class HAL
{
public:
	static HAL& getInstance();
	void set(uintptr_t port, uint8_t val, bool on);
	bool isSet(uintptr_t port, uint8_t val);
	bool lichtschrankeEinlauf();
	bool lichtschrankeAuslauf();
	InterruptController* getInterruptController();
	Bedienpanel* getBedienpanel();
	Ampel* getAmpel();
	Motor* getMotor();
	Weiche* getWeiche();
	Hoehenmesser* getHoehenmesser();
	Metalldetektor* getMetalldetektor();
	Rutsche* getRutsche();
private:
	HAL();
	virtual ~HAL();
	void toggle(uintptr_t port, uint8_t val);
	void out(uintptr_t port, uint8_t val);
	uint8_t in(uintptr_t port);
	mutexmap mutexe;
	InterruptController *interruptController;
	Bedienpanel *bedienpanel;
	Ampel *ampel;
	Motor *motor;
	Weiche *weiche;
	Hoehenmesser *hoehenmesser;
	Metalldetektor *metalldetektor;
	Rutsche *rutsche;
friend class InterruptController;
};

#endif /* HAL_H */
