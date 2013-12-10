#include "Beobachter.h"

	Beobachter::~Beobachter(){
	}

	void Beobachter::execute(){
	}

	void Beobachter::aktualisiereSignale(uint8_t iq, uint8_t state){

	}



bool Beobachter::operator==(const Beobachter& o){
	bool temp = false;
	if(&o != NULL){
		if(&(*this) == &(o)){
			temp = true;
		}
	}
	return temp;
}
