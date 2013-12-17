/**
 * @file    TestSerielleSchnittstelle.cpp
 * @date    06.11.2013
 * @author  Ruben Christian Buhl
 * @brief   TestSerielleSchnittstelle Implementierung
 */

#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <string>

#include "TestSerielleSchnittstelle.h"
#include "SerielleSchnittstelle.h"
#include "WerkstueckDaten.h"

using namespace std;

/**
 * Startet den Test der seriellen Schnittstelle.
 *
 * @param   automatik  Wahr, wenn der Test automatisch ausgefuehrt soll. Falsch, wenn der Test manuell ausgefuehrt werden soll.
 * @param   wiederholungen  Die Anzahl der Wiederholungen des Tests.
 *
 * Fuer jede Wiederholung des Tests werden einmal Daten gesendet und einmal Daten empfangen.
 * Dies ist in die Methoden senden() und empfangen() unterteilt.
 * Wenn der Test automatisch ausgefuehrt werden soll, wird der Test die bestimmte Anzahl Wiederholungen ausgefuehrt.
 * Wenn der Test manuell ausgefuehrt werden soll, wird auf eine beliebige Eingabe gewartet und dann der Test wiederholt.
 * In dem Fall bestimmt der Tester wie oft der Test wiederholt wird.
 * Wenn der Tester den in dem Makro KOMMANDO_TEST_BEENDEN definierten String eingibt wird das Testen beendet.
 */

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

/**
 * Testet das Senden von Daten ueber die SerielleSchnittstelle.
 *
 * Ein Werkstueck wird erstellt, mit zufaelligen Daten gefuellt und mittels der SerielleSchnittstelle gesendet.
 * Anschliessend werden die Daten des gesendeten Werkstuecks ausgegeben.
 */

void TestSerielleSchnittstelle::senden()
{
	struct Werkstueck werkstueck;

	srand(time(NULL));

	werkstueck.id = rand() % 100000;
	werkstueck.typ = BOHRUNG_OBEN_METALL;
	werkstueck.hoehen[0] = (rand() % 100000) / 10000.0;
	werkstueck.hoehen[1] = (rand() % 100000) / 10000.0;

	SerielleSchnittstelle::getInstance().sendeWerkstueckDaten(&werkstueck);

	cout << "Werkstueck gesendet" << endl;
	cout << "    ID: " << werkstueck.id << endl;
	cout << "    Typ: " << werkstueck.typ << endl;
	cout << "    Hoehe 1: " << werkstueck.hoehen[0] << endl;
	cout << "    Hoehe 2: " << werkstueck.hoehen[1] << endl;
}

/**
 * Testet das Empfangen von Daten ueber die SerielleSchnittstelle.
 *
 * Ein Werkstueck wird mittels der SerielleSchnittstelle empfangen.
 * Anschliessend werden die Daten des empfangenen Werkstuecks ausgegeben.
 */

void TestSerielleSchnittstelle::empfangen()
{
	struct Werkstueck werkstueck;

	SerielleSchnittstelle::getInstance().empfangeWerkstueckDaten(&werkstueck);

	cout << "Werkstueck empfangen" << endl;
	cout << "    ID: " << werkstueck.id << endl;
	cout << "    Typ: " << werkstueck.typ << endl;
	cout << "    Hoehe 1: " << werkstueck.hoehen[0] << endl;
	cout << "    Hoehe 2: " << werkstueck.hoehen[1] << endl;
}
