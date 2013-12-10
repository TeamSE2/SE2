#ifndef DISPATCHER_H
#define DISPATCHER_H
#include <stdint.h>
#include <list>
#include "HAWThread.h"
#include "Beobachter.h"
#include "HAL.h"
#include "PulsNachricht.h"
#include "SynBandEins.h"
#include "iterator"

// Laufband 1 Synchronisations Plaetze
#define VERLASSEN 0
#define UEBERGABE_START 1
#define UEBERGABE_ENDE 2

class Dispatcher: public thread::HAWThread{
public:
	~Dispatcher();
	static Dispatcher* getInstance();
	void anmelden(Beobachter *e, uint8_t iq, uint8_t port);
	void abmelden(Beobachter *e, uint8_t iq, uint8_t port);
	void benachrichtige(PulsNachricht *nachricht);

	void execute(void *arg);
	void shutdown();
private:
	static Dispatcher *instance;

	list<Beobachter*> lichtschranke_einlauf;
	list<Beobachter*> lichtschranke_hoehenmessung;
	list<Beobachter*> lichtschranke_auslauf;
	list<Beobachter*> lichtschranke_weiche;
	list<Beobachter*> hoehenmessung_check;
	list<Beobachter*> metalldetektor_check;
	list<Beobachter*> weiche_offen;
	list<Beobachter*> rutsche_voll;
	list<Beobachter*> taste_start;
	list<Beobachter*> taste_stopp;
	list<Beobachter*> taste_reset;
	list<Beobachter*> taste_estopp;

	list<Beobachter*> syn_verlassen;
	list<Beobachter*> syn_uebergabe_start;
	list<Beobachter*> syn_uebergabe_ende;


	struct sigevent event;
	int signalChannelID;

	Dispatcher();
	void aktualisiereBeobachter(list<Beobachter*> *l, uint8_t iq, uint8_t state);
	void initialize();
	void modList(bool add, Beobachter *e, uint8_t iq, uint8_t port);
	void addElement(list<Beobachter*> *l, Beobachter *e);
	void removeElement(list<Beobachter*> *l, Beobachter *e);
	void ausgeben(PulsNachricht *nachricht);
};
 
#endif
