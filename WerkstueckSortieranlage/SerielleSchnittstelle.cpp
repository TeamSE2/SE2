/*
 * SerielleSchnittstelle.cpp
 *
 *  Created on: 20.10.2013
 *      Author: Ruben Christian Buhl
 */

#include <unistd.h>
#include <libc.h>

#include "SerielleSchnittstelle.h"

SerielleSchnittstelle::SerielleSchnittstelle()
{
	pthread_mutex_init(&mutex, NULL);
}

SerielleSchnittstelle::~SerielleSchnittstelle()
{
	pthread_mutex_destroy(&mutex);
}

SerielleSchnittstelle& SerielleSchnittstelle::getInstance()
{
	static SerielleSchnittstelle serielleSchnittstelle;

	return serielleSchnittstelle;
}

void SerielleSchnittstelle::sendeWerkstueck(const Werkstueck* werkstueck)
{
	sendeDaten(werkstueck, sizeof(Werkstueck));
}

void SerielleSchnittstelle::empfangeWerkstueck(Werkstueck* werkstueck)
{
	empfangeDaten(werkstueck, sizeof(Werkstueck));
}

void SerielleSchnittstelle::sendeDaten(const void* buf, ssize_t nbyte)
{
	int fileDescriptor;
	int nbyteLeft = nbyte;

	pthread_mutex_lock(&mutex);

	fileDescriptor = open(DEVICE, O_RDWR | O_NOCTTY);

	do{
		nbyteLeft -= write(fileDescriptor, buf, nbyte);

		usleep(200000);
	}while(nbyteLeft);

	close(fileDescriptor);

	pthread_mutex_unlock(&mutex);
}

void SerielleSchnittstelle::empfangeDaten(void* buf, ssize_t nbyte)
{
	int fileDescriptor;
	int nbyteLeft = nbyte;

	pthread_mutex_lock(&mutex);

	fileDescriptor = open(DEVICE, O_RDWR | O_NOCTTY);
	do{

		nbyteLeft -= readcond(fileDescriptor, buf, nbyte, nbyte, 1, 0);

	}while(nbyteLeft);


	close(fileDescriptor);

	pthread_mutex_unlock(&mutex);
}
