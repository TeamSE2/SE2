/**
 * @file    TestInterruptController.cpp
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

#include <unistd.h>
#include <iostream>
#include <string>

#include "TestInterruptController.h"
#include "HAL.h"

using namespace std;

void TestInterruptController::starten(bool automatik, unsigned int sekunden)
{
	string eingabe;

	cout << "Test des interrupt controller gestartet" << endl;

	HAL::getInstance().getInterruptController()->start(NULL);

	if(automatik)
	{
		sleep(sekunden);
	}
	else
	{
		do
		{
			getline(cin, eingabe);
		}
		while(eingabe.compare(KOMMANDO_TEST_BEENDEN) != 0);
	}

	HAL::getInstance().getInterruptController()->stop();
	HAL::getInstance().getInterruptController()->join();

	cout << "Test des interrupt controller abgeschlossen" << endl;
}
