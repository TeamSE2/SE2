/**
 * @file    HAL.cpp
 * @date    19.10.2013
 * @author  Ruben Christian Buhl
 * @brief   HAL Implementierung
 */

#include "HAL.h"
#include "HWaccess.h"

/**
 * HAL Konstruktor
 *
 * Barrier und Mutexe werden initialisiert.
 * Control Port wird initialisiert.
 * Objekte werden erstellt.
 * InterruptController wird gestartet.
 */

HAL::HAL()
{
	pthread_barrier_init(&barrier, NULL, 2);

	pthread_mutex_init(&(mutexe[PORT_A]), NULL);
	pthread_mutex_init(&(mutexe[PORT_B]), NULL);
	pthread_mutex_init(&(mutexe[PORT_C]), NULL);

	out8(CONTROL, CONTROL_INITIALIZER);

	interruptController = new InterruptController();
	bedienpanel = new Bedienpanel();
	ampel = new Ampel();
	motor = new Motor();
	weiche = new Weiche();
	hoehenmesser = new Hoehenmesser();
	metalldetektor = new Metalldetektor();
	rutsche = new Rutsche();

	interruptController->start(&barrier);
}

/**
 * HAL Destruktor
 *
 * InterruptController wird gestoppt.
 * Objekte werden geloescht.
 * Mutexe werden zerstoert.
 */

HAL::~HAL()
{
	interruptController->stop();
	interruptController->join();

	delete interruptController;
	delete bedienpanel;
	delete ampel;
	delete motor;
	delete weiche;
	delete hoehenmesser;
	delete metalldetektor;
	delete rutsche;

	for(mutexmap::iterator mutexeIterator = mutexe.begin(); mutexeIterator != mutexe.end(); mutexeIterator++)
	{
		pthread_mutex_destroy(&(mutexeIterator->second));
	}
}

/**
 * Liefert Objekt des Singleton.
 *
 * @return  Einziges Objekt der HAL
 *
 * Singleton nach Meyers Singleton implementiert.
 */

HAL& HAL::getInstance()
{
	static HAL hal;

	return hal;
}

/**
 * Initialiert das Objekt der HAL.
 *
 * Muss vor Benutzung der HAL ein Mal aufgerufen werden.
 * Wartet auf die Threads, welche mit der Instanziierung der HAL gestartet wurden.
 * Barrier wird zerstoert.
 */

void HAL::initialize()
{
	pthread_barrier_wait(&(getInstance().barrier));
	pthread_barrier_destroy(&(getInstance().barrier));
}

/**
 * Setzt den Wert eines Port.
 *
 * @param   port  Der Port, dessen Wert gesetzt werden soll.
 * @param   val  Bit des Port, welches gesetzt werden sollen.
 * @param   on  Bestimmter Wert, auf welchen das Bit gesetzt werden sollen.
 *
 * Setzt den Wert eines Port, wenn der Port nicht bereits den bestimmten Wert besitzt.
 */

void HAL::set(uintptr_t port, uint8_t val, bool on)
{
	if(isSet(port, val) != on)
	{
		toggle(port, val);
	}
}

/**
 * Prueft ob ein Port einen bestimmten Wert besitzt.
 *
 * @param   port  Der Port, dessen Wert geprueft werden soll.
 * @param   val  Bestimmter Wert, auf welchen der Port geprueft werden soll.
 * @return  Wahr, wenn der Port den bestimmten Wert besitzt. Falsch, wenn nicht.
 *
 * Liest den Wert des Port und verknuepft ihn mittels UND-Operator mit dem bestimmten Wert.
 */

bool HAL::isSet(uintptr_t port, uint8_t val)
{
	return in(port) & val;
}

bool HAL::lichtschrankeEinlauf()
{
	return isSet(PORT_B, LICHTSCHRANKE_EINLAUF);
}

bool HAL::lichtschrankeAuslauf()
{
	return isSet(PORT_B, LICHTSCHRANKE_AUSLAUF);
}

/**
 * Schaltet bestimmte Bits eines Port um
 *
 * @param   port  Der Port, dessen Bits umgeschaltet werden sollen.
 * @param   val  Bestimmte Bits, welche umgeschaltet werden sollen.
 *
 * Liest den Wert des Port, verkuenpft ihn mittels exklusiv ODER-Operator mit den bestimmten Bits und schreibt das Ergebnis auf den Port.
 */

void HAL::toggle(uintptr_t port, uint8_t val)
{
	out(port, in(port) ^ val);
}

/**
 * Schreibt Thread sicher einen Wert auf einen Port.
 *
 * @param   port  Der Port, dessen Wert ueberschrieben werden soll.
 * @param   val  Der Wert, welcher auf den Port geschrieben werden soll.
 *
 * Sperrt den, dem Port zugehoerigen, Mutex, schreibt den Wert auf den Port und entsperrt den Mutex anschliessend wieder.
 */

void HAL::out(uintptr_t port, uint8_t val)
{
	pthread_mutex_lock(&(mutexe[port]));

	out8(port, val);

	pthread_mutex_unlock(&(mutexe[port]));
}

/**
 * Liest Thread sicher den Wert eines bestimmten Port.
 *
 * @param   port  Bestimmter Port, dessen Wert gelesen werden soll.
 * @return  Gelesener Wert der bestimmten Port.
 *
 * Sperrt den, dem Port zugehoerigen, Mutex, liest den Wert des bestimmten Port und entsperrt den Mutex anschliessend wieder.
 */

uint8_t HAL::in(uintptr_t port)
{
	uint8_t val;

	pthread_mutex_lock(&(mutexe[port]));

	val = in8(port);

	pthread_mutex_unlock(&(mutexe[port]));

	return val;
}

InterruptController* HAL::getInterruptController()
{
	return interruptController;
}

Bedienpanel* HAL::getBedienpanel()
{
	return bedienpanel;
}

Ampel* HAL::getAmpel()
{
	return ampel;
}

Motor* HAL::getMotor()
{
	return motor;
}

Weiche* HAL::getWeiche()
{
	return weiche;
}

Hoehenmesser* HAL::getHoehenmesser()
{
	return hoehenmesser;
}

Metalldetektor* HAL::getMetalldetektor()
{
	return metalldetektor;
}

Rutsche* HAL::getRutsche()
{
	return rutsche;
}
