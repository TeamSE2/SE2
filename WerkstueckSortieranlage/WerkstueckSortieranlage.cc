#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <string>

#include "HWaccess.h"
#include "TestKomponenten.h"
#include "TestSerielleSchnittstelle.h"
#include "TestInterruptController.h"
#include "SynBandEins.h"
#include "HAL.h"


#define KOMMANDO_PRAEFIX '-'
#define KOMMANDO_TEST "test"
#define KOMMANDO_AUTOMATIK "automatik"
#define PARAMETER_TEST_KOMPONENTEN "komponenten"
#define PARAMETER_TEST_SERIELLESCHNITTSTELLE "schnittstelle"
#define PARAMETER_TEST_INTERRUPTCONTROLLER "interrupts"

using namespace PetriNetzBandEins;
using namespace std;

int main(int argc, char *argv[])
{
	#ifdef SIMULATION
		IOaccess_open();
	#endif

	if(ThreadCtl(_NTO_TCTL_IO, 0) == -1)
	{
		return -1;
	}

	HAL::getInstance().initialize();
	Dispatcher::getInstance();
	if(argc > 1)
	{
		if(argv[1][0] == KOMMANDO_PRAEFIX && strlen(argv[1]) > 1)
		{
			string kommando1 = &(argv[1][1]);

			if(kommando1.compare(KOMMANDO_TEST) == 0 && argc > 2)
			{
				string parameter = argv[2];

				bool automatik = false;

				unsigned int automatik_parameter = 0;

				if(argc > 3)
				{
					if(argv[3][0] == KOMMANDO_PRAEFIX && strlen(argv[3]) > 1)
					{
						string kommando2 = &(argv[3][1]);

						if(kommando2.compare(KOMMANDO_AUTOMATIK) == 0 && argc > 4)
						{
							char *parameter2 = argv[4];

							if(strspn(parameter2, "1234567890") == strlen(parameter2))
							{
								automatik = true;

								automatik_parameter = atoi(parameter2);
							}
							else
							{
								cout << "WerkstueckSortieranlage: Ungueltiger Parameter: \"" << parameter2 << "\"" << endl;
							}
						}
						else
						{
							cout << "WerkstueckSortieranlage: Ungueltiges Kommando: \"" << kommando2 << "\"" << endl;
						}
					}
					else
					{
						cout << "WerkstueckSortieranlage: Ungueltiges Argument: \"" << argv[3] << "\"" << endl;
					}
				}

				if(parameter.compare(PARAMETER_TEST_KOMPONENTEN) == 0)
				{
					TestKomponenten::starten(automatik, automatik_parameter);
				}
				else if(parameter.compare(PARAMETER_TEST_SERIELLESCHNITTSTELLE) == 0)
				{
					TestSerielleSchnittstelle::starten(automatik, automatik_parameter);
				}
				else if(parameter.compare(PARAMETER_TEST_INTERRUPTCONTROLLER) == 0)
				{
					TestInterruptController::starten(automatik, automatik_parameter);
				}
				else
				{
					cout << "WerkstueckSortieranlage: Ungueltiger Parameter: \"" << parameter << "\"" << endl;
				}
			}
			else
			{
				cout << "WerkstueckSortieranlage: Ungueltiges Kommando: \"" << kommando1 << "\"" << endl;
			}
		}
		else
		{
			cout << "WerkstueckSortieranlage: Ungueltiges Argument: \"" << argv[1] << "\"" << endl;
		}
	}
	else
	{
		cout << "WerkstueckSortieranlage: Normaler Betrieb" << endl;
			Dispatcher::getInstance()->start(NULL);
			SynBandEins::getInstance();
			sleep(200);
			Dispatcher::getInstance()->stop();
			Dispatcher::getInstance()->join();
	}



	#ifdef SIMULATION
		IOaccess_close();
	#endif

	return EXIT_SUCCESS;
}
