#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include "HWaccess.h"
#include "MyThread.h"

using namespace thread;



int main(int argc, char *argv[]) {
#ifdef SIMULATION
	cout << "Simulation aktiv" << endl;
	cout << "Zum Aufbau der Verbindung muss Die Festo Simulation schon laufen." << endl;
	IOaccess_open(); // Baue die Verbindung zur Simulation auf
#endif

	MyThread thread;
	thread.start(NULL);

	sleep(30);

	thread.stop();
	thread.join();

#ifdef SIMULATION
	IOaccess_close(); // Schließe die Verbindung zur Simulation
#endif

	return EXIT_SUCCESS;
}
