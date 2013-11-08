/**
 * @file    TestSerielleSchnittstelle.cpp
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

#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <string>

#include "TestSerielleSchnittstelle.h"
#include "SerielleSchnittstelle.h"
#include "Werkstueck.h"

using namespace std;

void TestSerielleSchnittstelle::starten(bool automatik, unsigned int wiederholungen)
{
	string eingabe;

	cout << "Test der seriellen Schnittstelle gestartet" << endl;

	if(automatik)
	{
		for(unsigned int i = 0; i < wiederholungen; i++)
		{
			senden();
			empfangen();
		}
	}
	else
	{
		do
		{
			senden();
			empfangen();

			getline(cin, eingabe);
		}
		while(eingabe.compare(KOMMANDO_TEST_BEENDEN) != 0);
	}

	cout << "Test der seriellen Schnittstelle abgeschlossen" << endl;
}

void TestSerielleSchnittstelle::senden()
{
	struct Werkstueck werkstueck;

	werkstueck.id = rand() % 100000;
	werkstueck.typ = BOHRUNG_OBEN_METALL;
	werkstueck.hoehen[0] = (rand() % 100000) / 10000.0;
	werkstueck.hoehen[1] = (rand() % 100000) / 10000.0;

	SerielleSchnittstelle::getInstance().sendeWerkstueck(&werkstueck);

	cout << "Werkstueck gesendet" << endl;
	cout << "    ID: " << werkstueck.id << endl;
	cout << "    Typ: " << werkstueck.typ << endl;
	cout << "    Hoehe 1: " << werkstueck.hoehen[0] << endl;
	cout << "    Hoehe 2: " << werkstueck.hoehen[1] << endl;
}

void TestSerielleSchnittstelle::empfangen()
{
	struct Werkstueck werkstueck;

	SerielleSchnittstelle::getInstance().empfangeWerkstueck(&werkstueck);

	cout << "Werkstueck empfangen" << endl;
	cout << "    ID: " << werkstueck.id << endl;
	cout << "    Typ: " << werkstueck.typ << endl;
	cout << "    Hoehe 1: " << werkstueck.hoehen[0] << endl;
	cout << "    Hoehe 2: " << werkstueck.hoehen[1] << endl;
}
