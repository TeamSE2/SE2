#include <Weiche.h>
#include "HWaccess.h"
#include "Adressen.h"
#include <stdint.h>

namespace HAL {

	Weiche *Weiche::instance = NULL;

	 Weiche::Weiche(){

	}

	Weiche::~Weiche(){
		delete instance;
		instance = NULL;
	}

	Weiche* Weiche::getInstance(){
	    // Zugriffsrechte fuer den Zugriff auf die HW holen
	    if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
	        perror("ThreadCtl access failed\n");
	        return NULL;
	    }

	    if(instance == NULL){
	    	instance = getInstance();
	    }

		return instance;
	}

	void Weiche::weicheAuf(){
		uint8_t val = in8(PORT_A);
		out8(PORT_A, val | WEICHE_AUF);
	}

	void Weiche::weicheZu(){
		uint8_t val = in8(PORT_A);
		out8(PORT_A, val & ~WEICHE_AUF);
	}
}
