/*
 * TestKomponenten.cpp
 *
 *  Created on: 20.10.2013
 *      Author: Ruben Christian Buhl
 */

#include <unistd.h>
#include <iostream>
#include <string>

#include "TestKomponenten.h"
#include "HAL.h"

using namespace std;

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

void TestKomponenten::weiche(bool automatik, unsigned int sekunden)
{
	HAL::getInstance().getWeiche()->auf(true);

	cout << "Weiche auf" << endl;

	warten(automatik, sekunden, WEICHE_AUF_SEKUNDEN_MAXIMUM);

	HAL::getInstance().getWeiche()->auf(false);
}

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
