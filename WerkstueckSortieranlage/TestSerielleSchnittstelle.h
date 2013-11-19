/**
 * @file    TestSerielleSchnittstelle.h
 * @date    06.11.2013
 * @author  Ruben Christian Buhl
 * @brief   TestSerielleSchnittstelle Header
 */

#ifndef TESTSERIELLESCHNITTSTELLE_H
#define TESTSERIELLESCHNITTSTELLE_H

#define KOMMANDO_TEST_BEENDEN "beenden"

/**
 * Klasse zum Testen der Kommunikation ueber die SerielleSchnittstelle.
 *
 * Mit der statischen Methode starten() wird der Test der seriellen Schnittstelle gestartet.
 */

class TestSerielleSchnittstelle
{
public:
	static void starten(bool automatik, unsigned int wiederholungen);
private:
	static void senden();
	static void empfangen();
};

#endif /* TESTSERIELLESCHNITTSTELLE_H */
