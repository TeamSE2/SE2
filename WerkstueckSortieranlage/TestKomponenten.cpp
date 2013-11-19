/**
 * @file    TestKomponenten.cpp
 * @date    20.10.2013
 * @author  Ruben Christian Buhl
 * @brief   TestKomponenten Implementierung
 */

#include <unistd.h>
#include <iostream>
#include <string>

#include "TestKomponenten.h"
#include "HAL.h"

using namespace std;

/**
 * Startet den Komponententest.
 *
 * @param   automatik  Wahr, wenn der Test automatisch ausgefuehrt soll. Falsch, wenn der Test manuell ausgefuehrt werden soll.
 * @param   sekunden  Die Anzahl der Sekunden, in welcher eine Komponente angesteuert werden soll.
 *
 * Die Tests sind in Gruppen unterteilt.
 * Jede Gruppe wird in einer eigenen Methode getestet.
 * Die Parameter werden an diese Methoden weitergereicht.
 */

void TestKomponenten::starten(bool automatik, unsigned int sekunden)
{
	cout << "Test der Komponenten gestartet" << endl;

	ampel(automatik, sekunden);
	blinken(automatik, sekunden);
	motor(automatik, sekunden);
	weiche(automatik, sekunden);
	bedienpanel(automatik, sekunden);

	cout << "Test der Komponenten abgeschlossen" << endl;
}

/**
 * Testet das Leuchten der Ampel.
 *
 * @param   automatik  Wahr, wenn der Test automatisch ausgefuehrt soll. Falsch, wenn der Test manuell ausgefuehrt werden soll.
 * @param   sekunden  Die Anzahl der Sekunden, in welcher eine Komponente angesteuert werden soll.
 *
 * Schaltet eine Lampe der Ampel ein, ruft die Methode warten() auf und schaltet die Lampe wieder aus.
 * Dieser Vorgang wird fuer jede Lampe der Ampel wiederholt.
 * Die Parameter werden an die Methode warten() weitergereicht.
 */

void TestKomponenten::ampel(bool automatik, unsigned int sekunden)
{
	HAL::getInstance().getAmpel()->gruen(true);

	cout << "Ampel Gruen" << endl;

	warten(automatik, sekunden, 0);

	HAL::getInstance().getAmpel()->gruen(false);
	HAL::getInstance().getAmpel()->gelb(true);

	cout << "Ampel Gelb" << endl;

	warten(automatik, sekunden, 0);

	HAL::getInstance().getAmpel()->gelb(false);
	HAL::getInstance().getAmpel()->rot(true);

	cout << "Ampel Rot" << endl;

	warten(automatik, sekunden, 0);

	HAL::getInstance().getAmpel()->rot(false);
}

/**
 * Testet das Blinken der Ampel.
 *
 * @param   automatik  Wahr, wenn der Test automatisch ausgefuehrt soll. Falsch, wenn der Test manuell ausgefuehrt werden soll.
 * @param   sekunden  Die Anzahl der Sekunden, in welcher eine Komponente angesteuert werden soll.
 *
 * Schaltet die Blinken aller Lampen der Ampel ein, ruft die Methode warten() auf und schaltet alle Lampen wieder aus.
 * Die Parameter werden an die Methode warten() weitergereicht.
 */

void TestKomponenten::blinken(bool automatik, unsigned int sekunden)
{
	HAL::getInstance().getAmpel()->gruenBlinken(1000);
	HAL::getInstance().getAmpel()->gelbBlinken(200);
	HAL::getInstance().getAmpel()->rotBlinken(500);

	cout << "Ampel Blinken" << endl;

	warten(automatik, sekunden, 0);

	HAL::getInstance().getAmpel()->gruen(false);
	HAL::getInstance().getAmpel()->gelb(false);
	HAL::getInstance().getAmpel()->rot(false);
}

/**
 * Testet den Motor des Fliessbands.
 *
 * @param   automatik  Wahr, wenn der Test automatisch ausgefuehrt soll. Falsch, wenn der Test manuell ausgefuehrt werden soll.
 * @param   sekunden  Die Anzahl der Sekunden, in welcher eine Komponente angesteuert werden soll.
 *
 * Schaltet eine Funktion des Motors ein, ruft die Methode warten() auf und schaltet auf naechste die Funktion um.
 * Dieser Vorgang wird fuer jede Funktion des Motors wiederholt.
 * Die Parameter werden an die Methode warten() weitergereicht.
 */

void TestKomponenten::motor(bool automatik, unsigned int sekunden)
{
	HAL::getInstance().getMotor()->rechtslauf(true);

	cout << "Motor Rechtslauf" << endl;

	warten(automatik, sekunden, 0);

	HAL::getInstance().getMotor()->langsam(true);

	cout << "Motor Rechtslauf langsam" << endl;

	warten(automatik, sekunden, 0);

	HAL::getInstance().getMotor()->langsam(false);
	HAL::getInstance().getMotor()->stopp(true);

	cout << "Motor Stopp" << endl;

	warten(automatik, sekunden, 0);

	HAL::getInstance().getMotor()->stopp(false);
	HAL::getInstance().getMotor()->rechtslauf(false);
	HAL::getInstance().getMotor()->linkslauf(true);

	cout << "Motor Linkslauf" << endl;

	warten(automatik, sekunden, 0);

	HAL::getInstance().getMotor()->langsam(true);

	cout << "Motor Linkslauf langsam" << endl;

	warten(automatik, sekunden, 0);

	HAL::getInstance().getMotor()->langsam(false);
	HAL::getInstance().getMotor()->linkslauf(false);
}

/**
 * Testet das Oeffnen und Schliessen der Weiche.
 *
 * @param   automatik  Wahr, wenn der Test automatisch ausgefuehrt soll. Falsch, wenn der Test manuell ausgefuehrt werden soll.
 * @param   sekunden  Die Anzahl der Sekunden, in welcher eine Komponente angesteuert werden soll.
 *
 * Oeffnet die Weiche, ruft die Methode warten() auf und schliesst die Weiche wieder.
 * Die Parameter werden an die Methode warten() weitergereicht.
 */

void TestKomponenten::weiche(bool automatik, unsigned int sekunden)
{
	HAL::getInstance().getWeiche()->auf(true);

	cout << "Weiche auf" << endl;

	warten(automatik, sekunden, WEICHE_AUF_SEKUNDEN_MAXIMUM);

	HAL::getInstance().getWeiche()->auf(false);
}

/**
 * Testet die LED des Bedienpanel.
 *
 * @param   automatik  Wahr, wenn der Test automatisch ausgefuehrt soll. Falsch, wenn der Test manuell ausgefuehrt werden soll.
 * @param   sekunden  Die Anzahl der Sekunden, in welcher eine Komponente angesteuert werden soll.
 *
 * Schaltet eine LED des Bedienpanel ein, ruft die Methode warten() auf und schaltet die LED wieder aus.
 * Dieser Vorgang wird fuer jede LED des Bedienpanel wiederholt.
 * Die Parameter werden an die Methode warten() weitergereicht.
 */

void TestKomponenten::bedienpanel(bool automatik, unsigned int sekunden)
{
	HAL::getInstance().getBedienpanel()->led_Starttaste(true);

	cout << "Bedienpanel LED Starttaste" << endl;

	warten(automatik, sekunden, 0);

	HAL::getInstance().getBedienpanel()->led_Starttaste(false);
	HAL::getInstance().getBedienpanel()->led_Resettaste(true);

	cout << "Bedienpanel LED Resettaste" << endl;

	warten(automatik, sekunden, 0);

	HAL::getInstance().getBedienpanel()->led_Resettaste(false);
	HAL::getInstance().getBedienpanel()->led_Q1(true);

	cout << "Bedienpanel LED Q1" << endl;

	warten(automatik, sekunden, 0);

	HAL::getInstance().getBedienpanel()->led_Q1(false);
	HAL::getInstance().getBedienpanel()->led_Q2(true);

	cout << "Bedienpanel LED Q2" << endl;

	warten(automatik, sekunden, 0);

	HAL::getInstance().getBedienpanel()->led_Q2(false);
}

/**
 * Wartet abhaengig davon, ob der Test automatisch oder manuell ausgefuehrt werden soll.
 *
 * @param   automatik  Wahr, wenn der Test automatisch ausgefuehrt soll. Falsch, wenn der Test manuell ausgefuehrt werden soll.
 * @param   sekunden  Die Anzahl der Sekunden, welche gewartet werden soll.
 * @param   sekunden_maximum  Die Anzahl der Sekunden, welche maximal gewartet werden darf.
 *
 * Wenn der Test automatisch ausgefuehrt werden soll, wird die bestimmte Anzahl an Sekunden gewartet.
 * Es wird aber nicht laenger als die bestimmte maximale Anzahl an Sekunden gewartet, wenn diese ungleich 0 ist.
 * Wenn der Test manuell ausgefuehrt werden soll, wird auf eine beliebige Eingabe gewartet.
 * In dem Fall bestimmt der Tester wie lange die jeweilige Komponente getestet wird.
 * Eine moeglicherweise angegebene, maximale Anzahl an Sekunden die gewartet werden darf, wird dabei nicht beruecksichtigt.
 */

void TestKomponenten::warten(bool automatik, unsigned int sekunden, unsigned int sekunden_maximum)
{
	string eingabe;

	if(automatik)
	{
		if(sekunden_maximum != 0 && sekunden > sekunden_maximum)
		{
			sleep(sekunden_maximum);
		}
		else
		{
			sleep(sekunden);
		}
	}
	else
	{
		getline(cin, eingabe);
	}
}
