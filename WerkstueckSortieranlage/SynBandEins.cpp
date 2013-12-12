

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

}

SynBandEins* SynBandEins::getInstance(){

	if (instance == NULL) {
		instance = new SynBandEins();
	}

	return instance;
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

void SynBandEins::sendeZustandswechsel(uint8_t iq){
	PulsNachricht nachricht;
	int *val = NULL;
	int code = 1;

	nachricht.port = SYN_BAND_EINS;
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

void SynBandEins::resetSignale(){
	resetMotorStop();
}

void SynBandEins::aktualisiereSignale(){
	aktualisiereMotor();
}

void SynBandEins::setMotorStop(){
	motor_stop = true;
}

void SynBandEins::resetMotorStop(){
	motor_stop = false;
}

void SynBandEins::aktualisiereMotor(){
	if(motor_stop){
		HAL::getInstance().getMotor()->stopp(true);
	} else{
		HAL::getInstance().getMotor()->stopp(false);
	}
}

void SynBandEins::initialize(){
	signalConnectionID = HAL::getInstance().getInterruptController()->getSignalConnectionID();

	Einlaufsteuerung::getInstance();
	Hoehensteuerung::getInstance();
	Weichensteuerung::getInstance();
	Detektorsteuerung::getInstance();
	Uebergabesteuerung::getInstance();
	Auslaufsteuerung::getInstance();
}

}
