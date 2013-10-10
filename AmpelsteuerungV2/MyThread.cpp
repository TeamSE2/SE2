
#include "MyThread.h"
#include <iostream>
#include <unistd.h>
#include <cstdlib>

#include "HWaccess.h"
#include "Ampel.h"

using namespace std;
using namespace HAL;

namespace thread{

	MyThread::MyThread(){

	}

	MyThread::~MyThread(){

	}

	void MyThread::shutdown(){
		cout << "shut down..." << endl;
	}

	void MyThread::execute(void *arg){
	#ifdef SIMULATION
		cout << "Simulation aktiv" << endl;
		cout << "Zum Aufbau der Verbindung muss Die Festo Simulation schon laufen." << endl;
		IOaccess_open(); // Baue die Verbindung zur Simulation auf
	#endif

		Ampel *ampel = Ampel::getInstance();
		cout << "Thread startet" << endl;

			while(!isStopped()) {
				ampel->lampeRotAn();
				cout << "Rote Lampe An" << endl;
				sleep(1);
				ampel->lampeGelbAn();
				cout << "Gelbe Lampe An" << endl;
				sleep(1);
				ampel->lampeGruenAn();
				cout << "Gruene Lampe An" << endl;
				sleep(1);
				ampel->lampeRotAus();
				cout << "Rote Lampe Aus" << endl;
				sleep(1);
				ampel->lampeGelbAus();
				cout << "Gelbe Lampe Aus" << endl;
				sleep(1);
				ampel->lampeGruenAus();
				cout << "Gruene Lampe Aus" << endl;
				sleep(1);
			}

		#ifdef SIMULATION
			IOaccess_close(); // Schließe die Verbindung zur Simulation
		#endif

	}
}
