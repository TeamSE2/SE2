#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include "MyThread.h"

using namespace thread;

//Bredi

int main(int argc, char *argv[]) {

	MyThread thread;
	thread.start(NULL);

	sleep(30);

	thread.stop();
	thread.join();
	return EXIT_SUCCESS;
}
