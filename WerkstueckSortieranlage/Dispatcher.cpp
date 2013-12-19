
#include "Dispatcher.h"
using namespace std;
using namespace PetriNetzBandEins;

Dispatcher *Dispatcher::instance = NULL;

Dispatcher::Dispatcher(){
}

Dispatcher::~Dispatcher(){
	delete instance;
	instance = NULL;
}

Dispatcher* Dispatcher::getInstance(){

	if(instance == NULL){
		instance = new Dispatcher();
	}
	return instance;
}

void Dispatcher::anmelden(Beobachter *e){
	beobachter.push_front(e);
}

void Dispatcher::abmelden(Beobachter *e){
	beobachter.remove(e);
}



void Dispatcher::benachrichtige(uint8_t port, PulsNachricht *nachricht){
	list<Beobachter*>::iterator iter = beobachter.begin();
	list<Beobachter*>::iterator end = beobachter.end();
	bool execute = false;
	for(; iter != end ; iter++){
		execute = (*iter)->aktualisiereSignale(port ,nachricht->iq, nachricht->state);
		if(execute){
			(*iter)->execute();
		}else{
			(*iter)->schreibeSignale();
		}
	}
}


void Dispatcher::execute(void *arg){
	struct _pulse pulse;
	PulsNachricht *nachricht = NULL;
	initialize();
	while(!isStopped())
	{
		if(MsgReceivePulse(dispatcherChannelID, &pulse, sizeof(pulse), NULL) == -1)
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
			nachricht = (PulsNachricht*) &pulse.value.sival_int;

//			ausgeben(pulse.code, nachricht);
			SynBandEins::getInstance()->resetSignale();
			benachrichtige(pulse.code, nachricht);
			SynBandEins::getInstance()->aktualisiereSignale();
		}
	}

}


void Dispatcher::shutdown(){

}

void Dispatcher::initialize(){
	dispatcherChannelID = HAL::getInstance().getInterruptController()->getSignalChannelID();
	dispatcherConnectionID = HAL::getInstance().getInterruptController()->getSignalConnectionID();
}

int Dispatcher::getDispatcherConnectionID()
{
	return dispatcherChannelID;
}

int Dispatcher::getDispatcherChannelID()
{
	return dispatcherChannelID;
}


void Dispatcher::ausgeben(uint8_t port, PulsNachricht *nachricht)
{

	if(port == P_B)
	{
		switch(nachricht->iq)
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
	}



	if(port == P_C)
	{
		switch(nachricht->iq)
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
	}

	if(nachricht->state)
	{
		cout << " POSITIV" << endl;
	}
	else
	{
		cout << " NEGATIV" << endl;
	}
}
