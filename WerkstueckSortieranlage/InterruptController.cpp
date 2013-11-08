/**
 * @file    InterruptController.cpp
 * @date    03.11.2013
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

#include "InterruptController.h"
#include "HWaccess.h"

int isrConnectionID;

const struct sigevent* interruptServiceRoutine(void *arg, int id)
{
	struct sigevent *event = (struct sigevent *) arg;

	uint8_t status = in8(INTERRUPT_STATUS) & (INTERRUPT_STATUS_PORT_B | INTERRUPT_STATUS_PORT_C);
	uint8_t val;

	out8(INTERRUPT_STATUS, 0);

	switch(status)
	{
		case (INTERRUPT_STATUS_PORT_B | INTERRUPT_STATUS_PORT_C):
			val = in8(PORT_B);
			SIGEV_PULSE_INIT(event, isrConnectionID, SIGEV_PULSE_PRIO_INHERIT, INTERRUPT_STATUS_PORT_B, val);
			val = in8(PORT_C);
			SIGEV_PULSE_INIT(event, isrConnectionID, SIGEV_PULSE_PRIO_INHERIT, INTERRUPT_STATUS_PORT_C, val);
			break;
		case INTERRUPT_STATUS_PORT_B:
			val = in8(PORT_B);
			SIGEV_PULSE_INIT(event, isrConnectionID, SIGEV_PULSE_PRIO_INHERIT, INTERRUPT_STATUS_PORT_B, val);
			break;
		case INTERRUPT_STATUS_PORT_C:
			val = in8(PORT_C);
			SIGEV_PULSE_INIT(event, isrConnectionID, SIGEV_PULSE_PRIO_INHERIT, INTERRUPT_STATUS_PORT_C, val);
			break;
		default:
			event = NULL;
	}

	return event;
}

InterruptController::InterruptController()
{
}

InterruptController::~InterruptController()
{
}

void InterruptController::initialize()
{
	isrChannelID = ChannelCreate(0);

	if(isrChannelID == -1)
	{
		perror("InterruptController: isrChannelID ChannelCreate fehlgeschlagen");

		exit(EXIT_FAILURE);
	}

	isrConnectionID = ConnectAttach(0, 0, isrChannelID, _NTO_SIDE_CHANNEL, 0);

	if(isrConnectionID == -1)
	{
		perror("InterruptController: isrConnectionID ConnectAttach fehlgeschlagen");

		exit(EXIT_FAILURE);
	}

	SIGEV_PULSE_INIT(&event, isrConnectionID, SIGEV_PULSE_PRIO_INHERIT, 0, 0);

	interruptID = InterruptAttach(INTERRUPT_REQUEST, interruptServiceRoutine, &event, sizeof(event), 0);

	if(interruptID == -1)
	{
		perror("InterruptController: interruptID InterruptAttach fehlgeschlagen");

		exit(EXIT_FAILURE);
	}

	HAL::getInstance().out(INTERRUPT_STATUS, 0);
	HAL::getInstance().out(INTERRUPT_CONTROL, HAL::getInstance().in(INTERRUPT_CONTROL) | INTERRUPT_DISABLE);
	HAL::getInstance().out(INTERRUPT_CONTROL, HAL::getInstance().in(INTERRUPT_CONTROL) & ~(INTERRUPT_CONTROL_PORT_B | INTERRUPT_CONTROL_PORT_C));

	vals[PORT_B] = HAL::getInstance().in(PORT_B);
	vals[PORT_C] = HAL::getInstance().in(PORT_C);
}

void InterruptController::outputChange(uintptr_t port, uint8_t val)
{
	uint8_t change = val;

	if(port == INTERRUPT_STATUS_PORT_B)
	{
		change = change ^ vals[PORT_B];
	}
	else if(port == INTERRUPT_STATUS_PORT_C)
	{
		change = change ^ vals[PORT_C];
	}

	for(uint8_t i = 0x80; i > 0; i = i >> 1)
	{
		if(port == INTERRUPT_STATUS_PORT_B)
		{
			switch(change & i)
			{
				case LICHTSCHRANKE_EINLAUF:
					printf("LICHTSCHRANKE_EINLAUF");
					break;
				case LICHTSCHRANKE_HOEHENMESSUNG:
					printf("LICHTSCHRANKE_HOEHENMESSUNG");
					break;
				case HOEHENMESSUNG_CHECK:
					printf("HOEHENMESSUNG_CHECK");
					break;
				case LICHTSCHRANKE_WEICHE:
					printf("LICHTSCHRANKE_WEICHE");
					break;
				case METALLDETEKTOR_CHECK:
					printf("METALLDETEKTOR_CHECK");
					break;
				case WEICHE_OFFEN:
					printf("WEICHE_OFFEN");
					break;
				case RUTSCHE_VOLL:
					printf("RUTSCHE_VOLL");
					break;
				case LICHTSCHRANKE_AUSLAUF:
					printf("LICHTSCHRANKE_AUSLAUF");
					break;
			}
		}
		else if(port == INTERRUPT_STATUS_PORT_C)
		{
			switch(change & i)
			{
				case TASTE_START:
					printf("TASTE_START");
					break;
				case TASTE_STOPP:
					printf("TASTE_STOPP");
					break;
				case TASTE_RESET:
					printf("TASTE_RESET");
					break;
				case TASTE_ESTOPP:
					printf("TASTE_ESTOPP");
					break;
			}
		}

		if((change & i) > 0)
		{
			if((val & i) > 0)
			{
				printf(" POSITIV\n");
			}
			else
			{
				printf(" NEGATIV\n");
			}
		}
	}
}

void InterruptController::execute(void *arg)
{
	struct _pulse pulse;

	initialize();

	while(!isStopped())
	{
		if(MsgReceivePulse(isrChannelID, &pulse, sizeof(pulse), NULL) == -1)
		{
			if(isStopped())
			{
				break;
			}

			perror("InterruptController: isrChannelID MsgReceivePulse fehlgeschlagen");

			exit(EXIT_FAILURE);
		}
		else
		{
			outputChange(pulse.code, pulse.value.sival_int);

			vals[PORT_B] = HAL::getInstance().in(PORT_B);
			vals[PORT_C] = HAL::getInstance().in(PORT_C);
		}
	}
}

void InterruptController::shutdown()
{
}

void InterruptController::stop()
{
	HAWThread::stop();

	if(ConnectDetach(isrConnectionID) == -1)
	{
		perror("InterruptController: isrConnectionID ConnectDetach fehlgeschlagen");
	}

	if(ChannelDestroy(isrChannelID) == -1)
	{
		perror("InterruptController: isrChannelID ChannelDestroy fehlgeschlagen");
	}

//	if(InterruptDetach(interruptID) == -1)
//	{
//		perror("InterruptController: interruptID InterruptDetach fehlgeschlagen");
//	}
}
