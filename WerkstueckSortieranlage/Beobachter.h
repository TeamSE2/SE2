#ifndef BEOBACHTER_H
#define BEOBACHTER_H

#include <stdint.h>
#include <stdlib.h>

class Beobachter{
public:
	virtual ~Beobachter();
	virtual void aktualisiereSignale(uint8_t iq, uint8_t state);
	virtual void execute();
	bool operator==(const Beobachter& o);
};
#endif
