/**
 * @file    TestKomponenten.h
 * @date    20.10.2013
 * @author  Ruben Christian Buhl
 * @brief   TestKomponenten Header
 */

#ifndef TESTKOMPONENTEN_H
#define TESTKOMPONENTEN_H

#define WEICHE_AUF_SEKUNDEN_MAXIMUM 3

/**
 * Klasse zum Testen der Aktoren des HAL.
 *
 * Mit der statischen Methode starten() wird der Komponententest gestartet.
 */

class TestKomponenten
{
public:
	static void starten(bool automatik, unsigned int sekunden);
private:
	static void ampel(bool automatik, unsigned int sekunden);
	static void blinken(bool automatik, unsigned int sekunden);
	static void motor(bool automatik, unsigned int sekunden);
	static void weiche(bool automatik, unsigned int sekunden);
	static void bedienpanel(bool automatik, unsigned int sekunden);
	static void warten(bool automatik, unsigned int sekunden, unsigned int sekunden_maximum);
};

#endif /* TESTKOMPONENTEN_H */
