/**
 * @file    TestInterruptController.cpp
 * @date    06.11.2013
 * @author  Ruben Christian Buhl
 * @brief   TestInterruptController Implementierung
 */

#include <unistd.h>
#include <iostream>
#include <string>

#include "TestInterruptController.h"
#include "HAL.h"

using namespace std;

/**
 * Startet den Test der Sensoren des HAL.
 *
 * @param   automatik  Wahr, wenn der Test automatisch ausgefuehrt soll. Falsch, wenn der Test manuell ausgefuehrt werden soll.
 * @param   sekunden  Die Anzahl der Sekunden, welche gewartet werden soll.
 *
 * Es wird ein Objekt des TestInterruptController erstellt und dessen Thread gestartet.
 * Dieser Thread reagiert in der Methode execute() auf Pulse Messages des InterruptController.
 * Nach dem Starten des Thread wird gewartet und anschliessend der Thread gestoppt.
 * Wenn der Test automatisch ausgefuehrt werden soll, wird die bestimmte Anzahl an Sekunden gewartet.
 * Wenn der Test manuell ausgefuehrt werden soll, wird gewartet bis der Tester den in dem Makro KOMMANDO_TEST_BEENDEN definierten String eingibt.
 */

void TestInterruptController::starten(bool automatik, unsigned int sekunden)
{
	TestInterruptController testInterruptController;

	string eingabe;

	cout << "Test des interrupt controller gestartet" << endl;

	testInterruptController.start(NULL);

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

	testInterruptController.stop();
	testInterruptController.join();

	cout << "Test des interrupt controller abgeschlossen" << endl;
}

/**
 * Gibt eine Pulse Message des InterruptController aus.
 *
 * @param   code  Der Code der Pulse Message.
 * @param   val  Der Wert der Pulse Message.
 *
 * Wandelt den Code und den Wert der Pulse Message in lesbare Strings um und gibt sie aus.
 */

void TestInterruptController::ausgeben(bool code, int val)
{
	switch(val >> 8)
	{
		case LICHTSCHRANKE_EINLAUF:
			cout << "LICHTSCHRANKE_EINLAUF";
			break;
		case LICHTSCHRANKE_HOEHENMESSUNG:
			cout << "LICHTSCHRANKE_HOEHENMESSUNG";
			break;
		case HOEHENMESSUNG_CHECK:
			cout << "HOEHENMESSUNG_CHECK";
			break;
		case LICHTSCHRANKE_WEICHE:
			cout << "LICHTSCHRANKE_WEICHE";
			break;
		case METALLDETEKTOR_CHECK:
			cout << "METALLDETEKTOR_CHECK";
			break;
		case WEICHE_OFFEN:
			cout << "WEICHE_OFFEN";
			break;
		case RUTSCHE_VOLL:
			cout << "RUTSCHE_VOLL";
			break;
		case LICHTSCHRANKE_AUSLAUF:
			cout << "LICHTSCHRANKE_AUSLAUF";
			break;
	}

	switch(val)
	{
		case TASTE_START:
			cout << "TASTE_START";
			break;
		case TASTE_STOPP:
			cout << "TASTE_STOPP";
			break;
		case TASTE_RESET:
			cout << "TASTE_RESET";
			break;
		case TASTE_ESTOPP:
			cout << "TASTE_ESTOPP";
			break;
	}

	if(code)
	{
		cout << " POSITIV" << endl;
	}
	else
	{
		cout << " NEGATIV" << endl;
	}
}

/**
 * Initialisiert den TestInterruptController.
 *
 * Die Signal Channel ID wird vom InterruptController gelesen.
 */

void TestInterruptController::initialize()
{
	signalChannelID = HAL::getInstance().getInterruptController()->getSignalChannelID();
}

/**
 * Von HAWThread geerbte Methode, welche beim Starten des Thread aufgerufen wird.
 *
 * @param   arg  Der Parameter, welcher beim Starten des Thread uebergeben wird.
 *
 * Thread wird mit dem Aufruf von initialize() initialisiert.
 * Schleife des Thread wird gestartet und laeuft bis der Thread gestoppt wird.
 * In der Schleife werden die Pulse Messages des InterruptController empfangen und als Parameter an die Methode ausgeben() uebergeben.
 */

void TestInterruptController::execute(void *arg)
{
	struct _pulse pulse;

	initialize();

	while(!isStopped())
	{
		if(MsgReceivePulse(signalChannelID, &pulse, sizeof(pulse), NULL) == -1)
		{
			if(isStopped())
			{
				break;
			}

			perror("TestInterruptController: signalChannelID MsgReceivePulse fehlgeschlagen");

			exit(EXIT_FAILURE);
		}
		else
		{
			ausgeben(pulse.code, pulse.value.sival_int);
		}
	}
}

void TestInterruptController::shutdown()
{
}
