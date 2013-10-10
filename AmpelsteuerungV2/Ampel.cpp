
#include "Ampel.h"
#include "HWaccess.h"
#include "Adressen.h"
#include <stdint.h>

namespace HAL{

	Ampel *Ampel::instance = NULL;

	Ampel::Ampel(){
	    // Initialisierung der Digitalen IO Karte
	    out8(PORT_CTRL, 0x8A);
	    out8(PORT_A, 0x00);
	    out8(PORT_C, 0x00);
	}

	Ampel::~Ampel(){
		delete instance;
		instance = NULL;
	}

	Ampel* Ampel::getInstance(){
	    // Zugriffsrechte fuer den Zugriff auf die HW holen
	    if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
	        perror("ThreadCtl access failed\n");
	        return NULL;
	    }

	    if(instance == NULL){
	    	instance = new Ampel();
	    }

	    return instance;
	}

	void Ampel::lampeRotAn(){
	    uint8_t val = in8(PORT_A);
	    out8(PORT_A, val | BIT_7);
	}

	void Ampel::lampeGelbAn(){
		uint8_t val = in8(PORT_A);
		out8(PORT_A, val | BIT_6);
	}

	void Ampel::lampeGruenAn(){
		uint8_t val = in8(PORT_A);
		out8(PORT_A, val | BIT_5);
	}

	void Ampel::lampeRotAus(){
	    uint8_t val = in8(PORT_A);
	    out8(PORT_A, val & ~BIT_7);
	}

	void Ampel::lampeGelbAus(){
		uint8_t val = in8(PORT_A);
		out8(PORT_A, val & ~BIT_6);
	}

	void Ampel::lampeGruenAus(){
		uint8_t val = in8(PORT_A);
		out8(PORT_A, val & ~BIT_5);
	}
}
