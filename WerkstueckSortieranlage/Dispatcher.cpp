
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

void Dispatcher::modList(bool add, Beobachter *e, uint8_t iq, uint8_t port){

	list<Beobachter*> *temp;


	if(port == P_B){
		switch (iq) {
			case LICHTSCHRANKE_EINLAUF :
				temp = &lichtschranke_einlauf;
				break;
			case LICHTSCHRANKE_HOEHENMESSUNG :
				temp = &lichtschranke_hoehenmessung;
				break;
			case LICHTSCHRANKE_WEICHE :
				temp = &lichtschranke_weiche;
				break;
			case LICHTSCHRANKE_AUSLAUF :
				temp = &lichtschranke_auslauf;
				break;
			case HOEHENMESSUNG_CHECK :
				temp = &hoehenmessung_check;
				break;
			case METALLDETEKTOR_CHECK :
				temp = &metalldetektor_check;
				break;
			case WEICHE_OFFEN :
				temp = &weiche_offen;
				break;
			case RUTSCHE_VOLL :
				temp = &rutsche_voll;
				break;
			default:
				break;
		}
	}

	if(port == P_C){
		switch (iq) {
			case TASTE_START :
				temp = &taste_start;
				break;
			case TASTE_STOPP :
				temp = &taste_stopp;
				break;
			case TASTE_RESET :
				temp = &taste_reset;
				break;
			case TASTE_ESTOPP :
				temp = &taste_estopp;
				break;
			default:
				break;
		}
	}

	if(port == SYN_BAND_EINS){
		switch (iq) {
		case VERLASSEN :
			temp = &syn_verlassen;
			break;
		case UEBERGABE_START :
			temp = &syn_uebergabe_start;
			break;
		case UEBERGABE_ENDE :
			temp = &syn_uebergabe_ende;
			break;
		default:
			break;
		}
	}

	if(add){
		addElement(temp, e);
	}else{
		removeElement(temp, e);
	}

}

void Dispatcher::anmelden(Beobachter *e, uint8_t iq, uint8_t port){
	modList(true, e, iq, port);

}

void Dispatcher::abmelden(Beobachter *e, uint8_t iq, uint8_t port){
	modList(false, e, iq, port);
}


void Dispatcher::benachrichtige(PulsNachricht *nachricht){
	list<Beobachter*> *temp = NULL;

	if(nachricht->port == P_B){
		switch(nachricht->iq){
			case LICHTSCHRANKE_EINLAUF :
				temp = &lichtschranke_einlauf;
				break;
			case LICHTSCHRANKE_HOEHENMESSUNG :
				temp = &lichtschranke_hoehenmessung;
				break;
			case LICHTSCHRANKE_WEICHE :
				temp = &lichtschranke_weiche;
				break;
			case LICHTSCHRANKE_AUSLAUF :
				temp = &lichtschranke_auslauf;
				break;
			case HOEHENMESSUNG_CHECK :
				temp = &hoehenmessung_check;
				break;
			case METALLDETEKTOR_CHECK :
				temp = &metalldetektor_check;
				break;
			case WEICHE_OFFEN :
				temp = &weiche_offen;
				break;
			case RUTSCHE_VOLL :
				temp = &rutsche_voll;
				break;
			default:
				break;
		}
	}

	if(nachricht->port == P_C){
		switch(nachricht->iq){
			case TASTE_START :
				temp = &taste_start;
				break;
			case TASTE_STOPP :
				temp = &taste_stopp;
				break;
			case TASTE_RESET :
				temp = &taste_reset;
				break;
			case TASTE_ESTOPP :
				temp = &taste_estopp;
				break;
			default:
				break;
		}
	}

	if(nachricht->port == SYN_BAND_EINS){
		switch (nachricht->iq) {
		case VERLASSEN :
			temp = &syn_verlassen;
			break;
		case UEBERGABE_START :
			temp = &syn_uebergabe_start;
			break;
		case UEBERGABE_ENDE :
			temp = &syn_uebergabe_ende;
			break;
		default:
			break;
		}
	}

	aktualisiereBeobachter(temp, nachricht->iq, nachricht->state);
}

void Dispatcher::aktualisiereBeobachter(list<Beobachter*> *l, uint8_t iq, uint8_t state){
	list<Beobachter*>::iterator iter = (*l).begin();
	list<Beobachter*>::iterator end = (*l).end();
	for(; iter != end ; iter++){
//		cout << &(*(*iter)) << endl;
		(*iter)->aktualisiereSignale(iq, state);
		(*iter)->execute();
	}

}

void Dispatcher::execute(void *arg){
	struct _pulse pulse;
	PulsNachricht *nachricht = NULL;
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
			nachricht = (PulsNachricht*) &pulse.value.sival_int;
			ausgeben(nachricht);
			SynBandEins::getInstance()->resetSignale();
			benachrichtige(nachricht);
			SynBandEins::getInstance()->aktualisiereSignale();
		}
	}

}


void Dispatcher::shutdown(){

}

void Dispatcher::initialize(){
	signalChannelID = HAL::getInstance().getInterruptController()->getSignalChannelID();
}

void Dispatcher::addElement(list<Beobachter*> *l, Beobachter *e){
//	cout << e << endl;
	if (l != NULL) {
		(*l).push_front(e);
	}
}

void Dispatcher::removeElement(list<Beobachter*> *l, Beobachter *e){
	if (l != NULL) {
		(*l).remove(e);
	}
}

void Dispatcher::ausgeben(PulsNachricht *nachricht)
{

	if(nachricht->port == P_B)
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

	if(nachricht->port == P_C)
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
