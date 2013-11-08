/**
 * @file    TestInterruptController.h
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

#ifndef TESTINTERRUPTCONTROLLER_H
#define TESTINTERRUPTCONTROLLER_H

#define KOMMANDO_TEST_BEENDEN "beenden"

class TestInterruptController
{
public:
	static void starten(bool automatik, unsigned int sekunden);
};

#endif /* TESTINTERRUPTCONTROLLER_H */
