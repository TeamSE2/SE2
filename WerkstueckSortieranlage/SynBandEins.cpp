

#include "SynBandEins.h"

using namespace std;
namespace PetriNetzBandEins{

SynBandEins *SynBandEins::instance = NULL;

SynBandEins::SynBandEins(){
	initialize();
}

SynBandEins::~SynBandEins(){
	delete instance;
	instance = NULL;

	delete Einlaufsteuerung::getInstance();
	delete Hoehensteuerung::getInstance();
	delete Weichensteuerung::getInstance();
	delete Detektorsteuerung::getInstance();
	delete Uebergabesteuerung::getInstance();
	delete Auslaufsteuerung::getInstance();
	delete Fehlersteuerung::getInstance();
//	delete Notaussteuerung::getInstance();

}

SynBandEins* SynBandEins::getInstance(){

	if (instance == NULL) {
		instance = new SynBandEins();
	}

	return instance;
}

void SynBandEins::resetNetz(){
	syn[NEXT] = 1;
	syn[VERLASSEN] = 0;
	syn[UEBERGABE_START] = 0;
	syn[UEBERGABE_ENDE] = 0;
	syn[UEBERGABE_BEREIT] = 0;
	queueClear(queue_weiche);
	queueClear(queue_auslauf);
	queueClear(queue_hoehenmessung);
	queueClear(queue_detektor);
	queueClear(queue_uebergabe);
	resetSignale();

	Einlaufsteuerung::getInstance()->initNetz();
	Hoehensteuerung::getInstance()->initNetz();
	Weichensteuerung::getInstance()->initNetz();
	Detektorsteuerung::getInstance()->initNetz();
	Uebergabesteuerung::getInstance()->initNetz();
	Auslaufsteuerung::getInstance()->initNetz();
}

void SynBandEins::queueClear(queue<struct Werkstueck*> q){
	while(!q.empty()){
		q.pop();
	}
}

void SynBandEins::inkrementSynVerlassen(){
	syn[VERLASSEN]++;
	sendeZustandswechsel(VERLASSEN);
}

void SynBandEins::inkrementSynUebergabeStart(){
	syn[UEBERGABE_START]++;
	sendeZustandswechsel(UEBERGABE_START);
}

void SynBandEins::inkrementSynUebergabeEnde(){
	syn[UEBERGABE_ENDE]++;
	sendeZustandswechsel(UEBERGABE_ENDE);
}

void SynBandEins::inkrementSynUebergabeBereit(){
	syn[UEBERGABE_BEREIT]++;
	sendeZustandswechsel(UEBERGABE_BEREIT);
}

void SynBandEins::inkrementSynNext(){
	syn[NEXT]++;
	sendeZustandswechsel(NEXT);
}

void SynBandEins::sendeZustandswechsel(uint8_t iq){
	PulsNachricht nachricht;
	int *val = NULL;
	int code = SYN_BAND_EINS;

	nachricht.iq = iq;
	nachricht.state = 1;
	val = (int*)(&nachricht);

	MsgSendPulse(signalConnectionID, SIGEV_PULSE_PRIO_INHERIT, code, *val);
}

void SynBandEins::dekrementSynVerlassen(){
	syn[VERLASSEN]--;
}

void SynBandEins::dekrementSynUebergabeStart(){
	syn[UEBERGABE_START]--;
}

void SynBandEins::dekrementSynUebergabeEnde(){
	syn[UEBERGABE_ENDE]--;
}

void SynBandEins::dekrementSynUebergabeBereit(){
	syn[UEBERGABE_BEREIT]--;
}

void SynBandEins::dekrementSynNext(){
	syn[NEXT]--;
}

uint8_t SynBandEins::SynBandEins::getSynVerlassen(){
	return syn[VERLASSEN];
}

uint8_t SynBandEins::getSynUebergabeStart(){
	return syn[UEBERGABE_START];
}

uint8_t SynBandEins::getSynUebergabeEnde(){
	return syn[UEBERGABE_ENDE];
}

uint8_t SynBandEins::getSynUebergabeBereit(){
	return syn[UEBERGABE_BEREIT];
}

uint8_t SynBandEins::SynBandEins::getSynNext(){
	return syn[NEXT];
}

void SynBandEins::pushWerkstueckWeiche(struct Werkstueck *element){
	pushElement(&queue_weiche, element);
}

void SynBandEins::pushWerkstueckAuslauf(struct Werkstueck *element){
	pushElement(&queue_auslauf, element);
}

void SynBandEins::pushWerkstueckHoehenmessung(struct Werkstueck *element){
	pushElement(&queue_hoehenmessung, element);
}

void SynBandEins::pushWerkstueckDetektor(struct Werkstueck *element){
	pushElement(&queue_detektor, element);
}

void SynBandEins::pushWerkstueckUebergabe(struct Werkstueck *element){
	pushElement(&queue_uebergabe, element);
}

struct Werkstueck* SynBandEins::popWerkstueckWeiche(){
	return popElement(&queue_weiche);
}

struct Werkstueck* SynBandEins::popWerkstueckAuslauf(){
	return popElement(&queue_auslauf);
}

struct Werkstueck* SynBandEins::popWerkstueckHoehenmessung(){
	return popElement(&queue_hoehenmessung);
}

struct Werkstueck* SynBandEins::popWerkstueckDetektor(){
	return popElement(&queue_detektor);
}

struct Werkstueck* SynBandEins::popWerkstueckUebergabe(){
	return popElement(&queue_uebergabe);
}

struct Werkstueck* SynBandEins::getWerkstueckWeiche(){
	return getElement(&queue_weiche);
}

struct Werkstueck* SynBandEins::getWerkstueckAuslauf(){
	return getElement(&queue_auslauf);
}

struct Werkstueck* SynBandEins::getWerkstueckHoehenmessung(){
	return getElement(&queue_hoehenmessung);
}


void SynBandEins::pushElement(queue<struct Werkstueck*> *q, struct Werkstueck *element){
	if(element != NULL){
		q->push(element);
	}
}

struct Werkstueck* SynBandEins::popElement(queue<struct Werkstueck*> *q){
	Werkstueck* temp = NULL;

	if(!q->empty()){
		temp = q->front();
		q->pop();
	}

	return temp;
}

struct Werkstueck* SynBandEins::getElement(queue<struct Werkstueck*> *q){
	Werkstueck* temp = NULL;

	if(!q->empty()){
		temp = q->front();
	}

	return temp;
}

void SynBandEins::resetSignale(){
	motor_stop = false;
	reset_led_an = false;
	ampel_gruen = true;
//	timer_stop = false;
}

void SynBandEins::aktualisiereSignale(){
	HAL::getInstance().getMotor()->stopp(motor_stop);
	if(motor_stop){
		Timer::alle_anhalten();
		timer_stop = true;
	}

	if(timer_stop && !motor_stop){
		Timer::alle_fortsetzen();
		timer_stop = false;
	}

	HAL::getInstance().getBedienpanel()->led_Resettaste(reset_led_an);
	HAL::getInstance().getAmpel()->gruen(ampel_gruen);
}

void SynBandEins::setMotorStop(){
	motor_stop = true;
}

void SynBandEins::setResetLED(){
	reset_led_an = true;
}

void SynBandEins::setAmpelGruenAus(){
	ampel_gruen = false;
}

void SynBandEins::printWerkstueck(Werkstueck *ws){
	int loch = 0;
	int metall = 0;

	if(ws != NULL){
			if ((*ws).typ == BOHRUNG_OBEN || (*ws).typ == BOHRUNG_OBEN_METALL ) {
				loch = 1;
			}

			if ((*ws).typ == BOHRUNG_UNTEN_METALL || (*ws).typ == BOHRUNG_OBEN_METALL ) {
				metall = 1;
			}

				printf("Werkstueck ID      : %i \n"
						"Metall             : %i \n"
						"Loch oben          : %i \n"
						"Loch hoehe         : %i \n"
						"Werkstueck hoehe   : %i \n"
						, (*ws).id, metall, loch, (*ws).hoehen[0], (*ws).hoehen[1]);
		}
}

void SynBandEins::initialize(){
	syn[NEXT] = 1;
	signalConnectionID = HAL::getInstance().getInterruptController()->getSignalConnectionID();
	HAL::getInstance().getAmpel()->gruen(true);



	Auslaufsteuerung::getInstance();
	Uebergabesteuerung::getInstance();
	Weichensteuerung::getInstance();
	Detektorsteuerung::getInstance();
	Hoehensteuerung::getInstance();
	Einlaufsteuerung::getInstance();





//	Fehlersteuerung::getInstance();
//	Notaussteuerung::getInstance();
}

}
