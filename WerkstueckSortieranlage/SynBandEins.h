#ifndef SYN_BAND_EINS_H
#define SYN_BAND_EINS_H

#include <stdint.h>
#include <stdlib.h>
#include <queue>
#include "Werkstueck.h"
#include "PulsNachricht.h"
#include "HAL.h"
#include "Einlaufsteuerung.h"
#include "Hoehensteuerung.h"
#include "Weichensteuerung.h"
#include "Detektorsteuerung.h"
#include "Uebergabesteuerung.h"
#include "Auslaufsteuerung.h"

#define ANZ_SYN 3
#define VERLASSEN 0
#define UEBERGABE_START 1
#define UEBERGABE_ENDE 2

using namespace std;
namespace PetriNetzBandEins{


class SynBandEins{
public:


	static SynBandEins* getInstance();
	void inkrementSynVerlassen();
	void inkrementSynUebergabeStart();
	void inkrementSynUebergabeEnde();

	void dekrementSynVerlassen();
	void dekrementSynUebergabeStart();
	void dekrementSynUebergabeEnde();

	uint8_t getSynVerlassen();
	uint8_t getSynUebergabeStart();
	uint8_t getSynUebergabeEnde();

	void pushWerkstueckWeiche(struct Werkstueck *element);
	void pushWerkstueckAuslauf(struct Werkstueck *element);
	void pushWerkstueckHoehenmessung(struct Werkstueck *element);
	void pushWerkstueckDetektor(struct Werkstueck *element);
	void pushWerkstueckUebergabe(struct Werkstueck *element);
	void resetSignale();
	void aktualisiereSignale();
	void setMotorStop();
	void resetMotorStop();
	void aktualisiereMotor();

	struct Werkstueck* popWerkstueckWeiche();
	struct Werkstueck* popWerkstueckAuslauf();
	struct Werkstueck* popWerkstueckHoehenmessung();
	struct Werkstueck* popWerkstueckDetektor();
	struct Werkstueck* popWerkstueckUebergabe();


	virtual ~SynBandEins();
private:

	int signalConnectionID;
	bool motor_stop;
	pthread_mutex_t mutex[ANZ_SYN-1];
	uint8_t syn[ANZ_SYN-1];
	static SynBandEins *instance;

	queue<struct Werkstueck*> queue_weiche;
	queue<struct Werkstueck*> queue_auslauf;
	queue<struct Werkstueck*> queue_hoehenmessung;
	queue<struct Werkstueck*> queue_detektor;
	queue<struct Werkstueck*> queue_uebergabe;

	SynBandEins();
	void initialize();
	struct Werkstueck* popElement();
	void pushElement(queue<struct Werkstueck*> *q, struct Werkstueck *element);
	struct Werkstueck* popElement(queue<struct Werkstueck*> *q);
	void sendeZustandswechsel(uint8_t iq);
};
}
#endif


