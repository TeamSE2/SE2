#include <Motor.h>
#include "HWaccess.h"
#include "Adressen.h"
#include <stdint.h>

namespace HAL{

	Motor *Motor::instance = NULL;


	Motor::Motor(){

	}

	Motor::~Motor(){
		delete instance;
		instance = NULL;
	}

	Motor* Motor::getInstance(){
	    // Zugriffsrechte fuer den Zugriff auf die HW holen
	    if (-1 == ThreadCtl(_NTO_TCTL_IO, 0)) {
	        perror("ThreadCtl access failed\n");
	        return NULL;
	    }

	    if(instance == NULL){
	    	instance = new Motor();
	    }

	    return instance;
	}

	void Motor::motorRechtsLauf(){
		uint8_t val = in8(PORT_A);
		out8(PORT_A, ((val & ~MOTOR_LINKS) | MOTOR_RECHTS ));
	}

	void Motor::motorLinksLauf(){
		uint8_t val = in8(PORT_A);
		out8(PORT_A, (val & ~MOTOR_RECHTS) | MOTOR_LINKS);

	}

	void Motor::motorLangsam(){
		uint8_t val = in8(PORT_A);
		out8(PORT_A, val | MOTOR_LANGSAM);
	}

	void Motor::motorSchnell(){
		uint8_t val = in8(PORT_A);
		out8(PORT_A, val & ~MOTOR_LANGSAM);
	}

	void Motor::motorStop(){
		uint8_t val = in8(PORT_A);
		out8(PORT_A, val | MOTOR_STOP);
	}

	void Motor::motorStart(){
		uint8_t val = in8(PORT_A);
		out8(PORT_A, val & ~MOTOR_STOP);
	}


}
