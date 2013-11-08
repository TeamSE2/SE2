/**
 * @file    TestSerielleSchnittstelle.h
 * @date    06.11.2013
 * @author  Ruben Christian Buhl
 * @brief   Datei_Beschreibung_Kurz
 *
 * Datei_Beschreibung_Lang
 */

/**
 * Funktion_Beschreibung_Kurz
 *
 * @param   Parameter_Name  Parameter_Beschreibung
 * @return  Rueckgabe_Beschreibung
 *
 * Funktion_Beschreibung_Lang
 */

#ifndef TESTSERIELLESCHNITTSTELLE_H
#define TESTSERIELLESCHNITTSTELLE_H

#define KOMMANDO_TEST_BEENDEN "beenden"

class TestSerielleSchnittstelle
{
public:
	static void starten(bool automatik, unsigned int wiederholungen);
private:
	static void senden();
	static void empfangen();
};

#endif /* TESTSERIELLESCHNITTSTELLE_H */
