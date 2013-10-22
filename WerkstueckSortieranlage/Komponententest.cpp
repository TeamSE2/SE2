/*
 * Komponententest.cpp
 *
 *  Created on: 20.10.2013
 *      Author: Ruben Christian Buhl
 */

#include <unistd.h>
#include <iostream>

#include "Komponententest.h"
#include "HAL.h"

void Komponententest::starten()
{
	std::cout << "Komponententest gestartet" << std::endl;

	ampel();
	motor();
	weiche();
	bedienpanel();

	std::cout << "Komponententest abgeschlossen" << std::endl;
}

void Komponententest::ampel()
{
	HAL::getInstance().getAmpel().gruen();

	std::cout << "Ampel Gruen" << std::endl;

	sleep(SLEEP_SECONDS);

	HAL::getInstance().getAmpel().gruen();
	HAL::getInstance().getAmpel().gelb();

	std::cout << "Ampel Gelb" << std::endl;

	sleep(SLEEP_SECONDS);

	HAL::getInstance().getAmpel().gelb();
	HAL::getInstance().getAmpel().rot();

	std::cout << "Ampel Rot" << std::endl;

	sleep(SLEEP_SECONDS);

	HAL::getInstance().getAmpel().rot();
}

void Komponententest::motor()
{
	HAL::getInstance().getMotor().rechtslauf();

	std::cout << "Motor Rechtslauf" << std::endl;

	sleep(SLEEP_SECONDS);

	HAL::getInstance().getMotor().langsam();

	std::cout << "Motor Rechtslauf langsam" << std::endl;

	sleep(SLEEP_SECONDS);

	HAL::getInstance().getMotor().langsam();
	HAL::getInstance().getMotor().stopp();

	std::cout << "Motor Stopp" << std::endl;

	sleep(SLEEP_SECONDS);

	HAL::getInstance().getMotor().stopp();
	HAL::getInstance().getMotor().rechtslauf();
	HAL::getInstance().getMotor().linkslauf();

	std::cout << "Motor Linkslauf" << std::endl;

	sleep(SLEEP_SECONDS);

	HAL::getInstance().getMotor().langsam();

	std::cout << "Motor Linkslauf langsam" << std::endl;

	sleep(SLEEP_SECONDS);

	HAL::getInstance().getMotor().langsam();
	HAL::getInstance().getMotor().linkslauf();
}

void Komponententest::weiche()
{
	HAL::getInstance().getWeiche().auf();

	std::cout << "Weiche auf" << std::endl;

	sleep(SLEEP_SECONDS);

	HAL::getInstance().getWeiche().auf();
}

void Komponententest::bedienpanel()
{
	HAL::getInstance().getBedienpanel().led_Starttaste();

	std::cout << "Bedienpanel LED Starttaste" << std::endl;

	sleep(SLEEP_SECONDS);

	HAL::getInstance().getBedienpanel().led_Starttaste();
	HAL::getInstance().getBedienpanel().led_Resettaste();

	std::cout << "Bedienpanel LED Resettaste" << std::endl;

	sleep(SLEEP_SECONDS);

	HAL::getInstance().getBedienpanel().led_Resettaste();
	HAL::getInstance().getBedienpanel().led_Q1();

	std::cout << "Bedienpanel LED Q1" << std::endl;

	sleep(SLEEP_SECONDS);

	HAL::getInstance().getBedienpanel().led_Q1();
	HAL::getInstance().getBedienpanel().led_Q2();

	std::cout << "Bedienpanel LED Q2" << std::endl;

	sleep(SLEEP_SECONDS);

	HAL::getInstance().getBedienpanel().led_Q2();
}
