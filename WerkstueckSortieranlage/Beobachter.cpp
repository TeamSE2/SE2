#include "Beobachter.h"

	Beobachter::~Beobachter(){
	}

	void Beobachter::execute(){
	}

	bool Beobachter::aktualisiereSignale(uint8_t port, uint8_t iq, uint8_t state){
		return false;
	}

	void Beobachter::schreibeSignale(){
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
