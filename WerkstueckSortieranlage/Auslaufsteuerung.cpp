#include "Auslaufsteuerung.h"
#include "Timer.h"


namespace PetriNetzBandEins {

Auslaufsteuerung *Auslaufsteuerung::instance = NULL;

Auslaufsteuerung::Auslaufsteuerung(){
	initNetz();
	Dispatcher::getInstance()->anmelden(this);
}

Auslaufsteuerung::~Auslaufsteuerung(){
	Dispatcher::getInstance()->abmelden(this);
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
	plaetze[CHECK_1] = 0;
	plaetze[CHECK_2] = 0;
	plaetze[WENDEN_1] = 0;
	plaetze[WENDEN_2] = 0;
	plaetze[UEBERGABE] = 0;
	plaetze[WARTE_A] = 0;
	eingang[LICHTSCHRANKE_A] = 1;
	eingang[LOCH] = 0;
	eingang[METALL_A] = 0;
	eingang[TIMER_INT] = 0;
//	timer.tv_nsec = 0;
//	timer.tv_sec = 1;
}

void Auslaufsteuerung::ladeWerkstueck(){
	temp_ws = SynBandEins::getInstance()->popWerkstueckAuslauf();
	if(temp_ws != NULL){
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
}

bool Auslaufsteuerung::aktualisiereSignale(uint8_t port, uint8_t iq, uint8_t state){
 bool execute = false;

 	 if(port == P_B){
 		 if(iq == LICHTSCHRANKE_AUSLAUF){
 			 eingang[LICHTSCHRANKE_A] = state;
 			 execute = true;
 		 }
 	 }

 	 if(port == SYN_BAND_EINS){
 		 if(iq == UEBERGABE_ENDE){
 			 execute = true;
 		 }
 	 }

 	 if(port == TIMER_PULSE_CODE){
  		 if(iq == timer_id){
 			 eingang[TIMER_INT] = 1;
 			 execute = true;
 		 }
 	 }

	 return execute;
}

void Auslaufsteuerung::schreibeSignale(){

//	if(plaetze[WENDEN_1] || plaetze[WENDEN_2] || plaetze[UEBERGABE]){
//		SynBandEins::getInstance()->setMotorStop();
//	}
	if(plaetze[WENDEN_1] || plaetze[WENDEN_2]){
		SynBandEins::getInstance()->setAmpelGruenAus();
		HAL::getInstance().getAmpel()->gelbBlinken(1000);
	}else{
		HAL::getInstance().getAmpel()->gelb(false);
	}


}

void Auslaufsteuerung::transitionenAusfuehren(){

		if(plaetze[GZ] && !plaetze[CHECK_1] && !eingang[LICHTSCHRANKE_A]){
			ladeWerkstueck();
			if(temp_ws != NULL){
				plaetze[GZ] = 0;
				plaetze[CHECK_1] = 1;
			}

			printf("Auslauf: 1:  GZ: %i,CHECK_1: %i, CHECK_2: %i, WENDEN_1: %i, WENDEN_2: %i, UEBERGABE: %i, WARTE_A: %i\n"
								,plaetze[GZ], plaetze[CHECK_1], plaetze[CHECK_2], plaetze[WENDEN_1], plaetze[WENDEN_2], plaetze[UEBERGABE], plaetze[WARTE_A]);

		}

	if(temp_ws != NULL){
		if(plaetze[CHECK_1] && !plaetze[CHECK_2] && eingang[LOCH]){
			plaetze[CHECK_1] = 0;
			plaetze[CHECK_2] = 1;
			printf("Auslauf: 2:  GZ: %i,CHECK_1: %i, CHECK_2: %i, WENDEN_1: %i, WENDEN_2: %i, UEBERGABE: %i, WARTE_A: %i\n"
								,plaetze[GZ], plaetze[CHECK_1], plaetze[CHECK_2], plaetze[WENDEN_1], plaetze[WENDEN_2], plaetze[UEBERGABE], plaetze[WARTE_A]);

		}

		if(plaetze[CHECK_1] && !plaetze[WENDEN_1] && !eingang[LOCH]){
			plaetze[CHECK_1] = 0;
			plaetze[WENDEN_1] = 1;
			SynBandEins::getInstance()->inkrementSynMotorStop();
			printf("Auslauf: 3:  GZ: %i,CHECK_1: %i, CHECK_2: %i, WENDEN_1: %i, WENDEN_2: %i, UEBERGABE: %i, WARTE_A: %i\n"
								,plaetze[GZ], plaetze[CHECK_1], plaetze[CHECK_2], plaetze[WENDEN_1], plaetze[WENDEN_2], plaetze[UEBERGABE], plaetze[WARTE_A]);
		}

		if(plaetze[CHECK_2] && !plaetze[WENDEN_1] && eingang[METALL_A]){
			plaetze[CHECK_2] = 0;
			plaetze[WENDEN_1] = 1;
			SynBandEins::getInstance()->inkrementSynMotorStop();
			printf("Auslauf: 4:  GZ: %i,CHECK_1: %i, CHECK_2: %i, WENDEN_1: %i, WENDEN_2: %i, UEBERGABE: %i, WARTE_A: %i\n"
								,plaetze[GZ], plaetze[CHECK_1], plaetze[CHECK_2], plaetze[WENDEN_1], plaetze[WENDEN_2], plaetze[UEBERGABE], plaetze[WARTE_A]);
		}

		if(plaetze[CHECK_2] && !plaetze[UEBERGABE] && !eingang[METALL_A]){
			plaetze[CHECK_2] = 0;
			plaetze[UEBERGABE] = 1;
			SynBandEins::getInstance()->inkrementSynVerlassen();
			printf("Auslauf: 5:  GZ: %i,CHECK_1: %i, CHECK_2: %i, WENDEN_1: %i, WENDEN_2: %i, UEBERGABE: %i, WARTE_A: %i\n"
								,plaetze[GZ], plaetze[CHECK_1], plaetze[CHECK_2], plaetze[WENDEN_1], plaetze[WENDEN_2], plaetze[UEBERGABE], plaetze[WARTE_A]);
		}

		if(plaetze[WENDEN_1] && !plaetze[WENDEN_2] && eingang[LICHTSCHRANKE_A]){
			plaetze[WENDEN_1] = 0;
			plaetze[WENDEN_2] = 1;
			printf("6:  GZ: %i,CHECK_1: %i, CHECK_2: %i, WENDEN_1: %i, WENDEN_2: %i, UEBERGABE: %i, WARTE_A: %i\n"
								,plaetze[GZ], plaetze[CHECK_1], plaetze[CHECK_2], plaetze[WENDEN_1], plaetze[WENDEN_2], plaetze[UEBERGABE], plaetze[WARTE_A]);
		}

		if(plaetze[WENDEN_2] && !plaetze[UEBERGABE] && !eingang[LICHTSCHRANKE_A]){
			plaetze[WENDEN_2] = 0;
			plaetze[UEBERGABE] = 1;
			SynBandEins::getInstance()->inkrementSynMotorStop();
			SynBandEins::getInstance()->inkrementSynVerlassen();
			printf("Auslauf: 7:  GZ: %i,CHECK_1: %i, CHECK_2: %i, WENDEN_1: %i, WENDEN_2: %i, UEBERGABE: %i, WARTE_A: %i\n"
								,plaetze[GZ], plaetze[CHECK_1], plaetze[CHECK_2], plaetze[WENDEN_1], plaetze[WENDEN_2], plaetze[UEBERGABE], plaetze[WARTE_A]);
		}

		if(plaetze[UEBERGABE] && !plaetze[GZ] && SynBandEins::getInstance()->getSynUebergabeEnde()){
			SynBandEins::getInstance()->dekrementSynUebergabeEnde();
			plaetze[UEBERGABE] = 0;
			plaetze[GZ] = 1;
//			plaetze[WARTE_A] = 1;
//			SynBandEins::getInstance()->inkrementSynNext();
			SerielleSchnittstelle::getInstance().sendeNachricht(START_MOTOR);
			free(temp_ws);
			temp_ws = NULL;
//			timer_id = Timer::starten(timer);
			printf("Auslauf: 8:  GZ: %i,CHECK_1: %i, CHECK_2: %i, WENDEN_1: %i, WENDEN_2: %i, UEBERGABE: %i, WARTE_A: %i\n"
								,plaetze[GZ], plaetze[CHECK_1], plaetze[CHECK_2], plaetze[WENDEN_1], plaetze[WENDEN_2], plaetze[UEBERGABE], plaetze[WARTE_A]);
		}

		//todo: hier warten bis Werkstueck Band verlassen hat.
//		if(plaetze[WARTE_A] && !plaetze[GZ] && eingang[TIMER_INT]){
//			eingang[TIMER_INT] = 0;
////			SynBandEins::getInstance()->inkrementSynUebergabeEnde();
//			SynBandEins::getInstance()->inkrementSynVerlassen();
////			SynBandEins::getInstance()->printWerkstueck(temp_ws);
//			plaetze[WARTE_A] = 0;
//			plaetze[GZ] = 1;
//			printf("Auslauf: 9:  GZ: %i,CHECK_1: %i, CHECK_2: %i, WENDEN_1: %i, WENDEN_2: %i, UEBERGABE: %i, WARTE_A: %i\n"
//								,plaetze[GZ], plaetze[CHECK_1], plaetze[CHECK_2], plaetze[WENDEN_1], plaetze[WENDEN_2], plaetze[UEBERGABE], plaetze[WARTE_A]);
//
//		}
	}
}

void Auslaufsteuerung::execute(){
	transitionenAusfuehren();
	schreibeSignale();
}


}
