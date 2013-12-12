#ifndef BEOBACHTER_H
#define BEOBACHTER_H

#include <stdint.h>
#include <stdlib.h>

class Beobachter{
public:
	virtual ~Beobachter();
	virtual bool aktualisiereSignale(uint8_t port, uint8_t iq, uint8_t state);
	virtual void execute();
	virtual void schreibeSignale();
	bool operator==(const Beobachter& o);
};
#endif
