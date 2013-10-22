#include <cstdlib>
#include <unistd.h>

#include "HWaccess.h"
#include "Komponententest.h"

int main(int argc, char *argv[])
{
	#ifdef SIMULATION
		IOaccess_open();
	#endif

	if(ThreadCtl(_NTO_TCTL_IO, 0) == -1)
	{
		return -1;
	}

	Komponententest::starten();

	#ifdef SIMULATION
		IOaccess_close();
	#endif

	return EXIT_SUCCESS;
}
