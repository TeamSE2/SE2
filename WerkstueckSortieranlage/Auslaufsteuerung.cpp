#include "Auslaufsteuerung.h"


namespace PetriNetzBandEins {

Auslaufsteuerung *Auslaufsteuerung::instance = NULL;

Auslaufsteuerung::Auslaufsteuerung(){
	Dispatcher::getInstance()->anmelden(this, LICHTSCHRANKE_AUSLAUF, P_B);

}

Auslaufsteuerung::~Auslaufsteuerung(){
	Dispatcher::getInstance()->abmelden(this, LICHTSCHRANKE_AUSLAUF, P_B);

	delete instance;
	instance = NULL;
}

Auslaufsteuerung* Auslaufsteuerung::getInstance(){
	if(instance == NULL){
		instance = new Auslaufsteuerung();
	}

	return instance;
}

void Auslaufsteuerung::initNetz(){
	plaetze[GZ] = 1;
	plaetze[CHECK] = 0;
	plaetze[WENDEN_1] = 0;
	plaetze[WENDEN_2] = 0;
	plaetze[UEBERGABE] = 0;
	plaetze[WARTE_A] = 0;
}

void Auslaufsteuerung::ladeWerkstueck(){
	temp_ws = SynBandEins::getInstance()->popWerkstueckAuslauf();

	if ((*temp_ws).typ == BOHRUNG_OBEN || (*temp_ws).typ == BOHRUNG_OBEN_METALL ) {
		eingang[LOCH] = 1;
	}else{
		eingang[LOCH] = 0;
	}

	if ((*temp_ws).typ == BOHRUNG_UNTEN_METALL || (*temp_ws).typ == BOHRUNG_OBEN_METALL ) {
		eingang[METALL_A] = 1;
	}else{
		eingang[METALL_A] = 0;
	}
}

void Auslaufsteuerung::aktualisiereSignale(uint8_t iq, uint8_t state){

	 if(iq == LICHTSCHRANKE_EINLAUF){
		 eingang[LICHTSCHRANKE_A] = state;
	 }
}

void Auslaufsteuerung::schreibeSignale(){

	if(plaetze[WENDEN_1] || plaetze[WENDEN_2] || plaetze[UEBERGABE]){
		SynBandEins::getInstance()->setMotorStop();
		//stop Timer
	}


}

void Auslaufsteuerung::transitionenAusfuehren(){

	if(plaetze[GZ] && !plaetze[CHECK] && !eingang[LICHTSCHRANKE_A] && eingang[LOCH]){
		plaetze[GZ] = 0;
		plaetze[CHECK] = 1;
		ladeWerkstueck();
	}

	if(plaetze[GZ] && !plaetze[WENDEN_1] && !eingang[LICHTSCHRANKE_A] && !eingang[LOCH]){
		plaetze[GZ] = 0;
		plaetze[WENDEN_1] = 1;
		ladeWerkstueck();
	}

	if(plaetze[CHECK] && !plaetze[WENDEN_1] && eingang[METALL_A]){
		plaetze[CHECK] = 0;
		plaetze[WENDEN_1] = 1;
	}

	if(plaetze[CHECK] && !plaetze[UEBERGABE] && !eingang[METALL_A]){
		plaetze[CHECK] = 0;
		plaetze[UEBERGABE] = 1;
	}

	if(plaetze[WENDEN_1] && !plaetze[WENDEN_2] && eingang[LICHTSCHRANKE_A]){
		plaetze[WENDEN_1] = 0;
		plaetze[WENDEN_2] = 1;
	}

	if(plaetze[WENDEN_2] && !plaetze[UEBERGABE] && !eingang[LICHTSCHRANKE_A]){
		plaetze[WENDEN_2] = 0;
		plaetze[UEBERGABE] = 1;
	}

	if(plaetze[UEBERGABE] && !plaetze[WARTE_A] && SynBandEins::getInstance()->getSynUebergabeStart()){
		SynBandEins::getInstance()->dekrementSynUebergabeStart();
		plaetze[UEBERGABE] = 0;
		plaetze[WARTE_A] = 1;
	}

	//todo: hier warten bis Werkstueck Band verlassen hat.
	if(plaetze[WARTE_A] && !plaetze[GZ]){
		SynBandEins::getInstance()->inkrementSynUebergabeEnde();
		SynBandEins::getInstance()->inkrementSynVerlassen();
		plaetze[WARTE] = 0;
		plaetze[GZ] = 1;
	}
}

void Auslaufsteuerung::execute(){
	transitionenAusfuehren();
	schreibeSignale();
}


}
