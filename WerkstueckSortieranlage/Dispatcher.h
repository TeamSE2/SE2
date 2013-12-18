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


class Dispatcher: public thread::HAWThread{
public:
	~Dispatcher();
	static Dispatcher* getInstance();
	void anmelden(Beobachter *e);
	void abmelden(Beobachter *e);
	void benachrichtige(uint8_t port, PulsNachricht *nachricht);

	int getDispatcherConnectionID();
	int getDispatcherChannelID();

	void execute(void *arg);
	void shutdown();
private:
	static Dispatcher *instance;

	list<Beobachter*> beobachter;

	int dispatcherConnectionID;
	int dispatcherChannelID;

	Dispatcher();
	void initialize();

	void ausgeben(uint8_t port, PulsNachricht *nachricht);
};
 
#endif
