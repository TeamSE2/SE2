#include <cstdlib>
#include <iostream>
#include <unistd.h>

#include "HWaccess.h"
#include "SerielleSchnittstelle.h"
#include "HAL.h"
#include "Werkstueck.h"

//int main(int argc, char *argv[])
//{
//	#ifdef SIMULATION
//		IOaccess_open();
//	#endif
//
//	if(ThreadCtl(_NTO_TCTL_IO, 0) == -1)
//	{
//		return -1;
//	}
//
//	struct Werkstueck werkstueck = {1, BOHRUNG_OBEN_METALL, {3.7, 5.2}};
//
//	std::cout << "Werkstueck ID: " << werkstueck.id << " Typ: " << werkstueck.typ << " 1. hoehe" << werkstueck.hoehen[0] << " 2. hoehe" << werkstueck.hoehen[1] << std::endl;
//
//	SerielleSchnittstelle::getInstance().sendeWerkstueck(&werkstueck);
//
//	#ifdef SIMULATION
//		IOaccess_close();
//	#endif
//
//	return EXIT_SUCCESS;
//}
