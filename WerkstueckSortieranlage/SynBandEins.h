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

// Laufband 1 Synchronisations Plaetze
#define ANZ_SYN 4
#define VERLASSEN 0
#define UEBERGABE_START 1
#define UEBERGABE_ENDE 2
#define UEBERGABE_BEREIT 3

using namespace std;
namespace PetriNetzBandEins{


class SynBandEins{
public:


	static SynBandEins* getInstance();
	void resetNetz();
	void inkrementSynVerlassen();
	void inkrementSynUebergabeStart();
	void inkrementSynUebergabeEnde();
	void inkrementSynUebergabeBereit();

	void dekrementSynVerlassen();
	void dekrementSynUebergabeStart();
	void dekrementSynUebergabeEnde();
	void dekrementSynUebergabeBereit();

	uint8_t getSynVerlassen();
	uint8_t getSynUebergabeStart();
	uint8_t getSynUebergabeEnde();
	uint8_t getSynUebergabeBereit();

	void pushWerkstueckWeiche(struct Werkstueck *element);
	void pushWerkstueckAuslauf(struct Werkstueck *element);
	void pushWerkstueckHoehenmessung(struct Werkstueck *element);
	void pushWerkstueckDetektor(struct Werkstueck *element);
	void pushWerkstueckUebergabe(struct Werkstueck *element);
	void resetSignale();
	void aktualisiereSignale();
	void setMotorStop();
	void setResetLED();

	struct Werkstueck* popWerkstueckWeiche();
	struct Werkstueck* popWerkstueckAuslauf();
	struct Werkstueck* popWerkstueckHoehenmessung();
	struct Werkstueck* popWerkstueckDetektor();
	struct Werkstueck* popWerkstueckUebergabe();

	struct Werkstueck* getWerkstueckWeiche();
	struct Werkstueck* getWerkstueckAuslauf();
	struct Werkstueck* getWerkstueckHoehenmessung();

	virtual ~SynBandEins();
private:

	int signalConnectionID;
	bool motor_stop;
	bool reset_led_an;
	pthread_mutex_t mutex[ANZ_SYN];
	uint8_t syn[ANZ_SYN];
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
	struct Werkstueck* getElement(queue<struct Werkstueck*> *q);
	void sendeZustandswechsel(uint8_t iq);
	void queueClear(queue<struct Werkstueck*> q);
};
}
#endif


