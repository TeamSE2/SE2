#ifndef PETRINETZ_H
#define PETRINETZ_H

class PetriNetz{
public:
	virtual ~PetriNetz();
	virtual void initNetz() = 0;
	virtual void ladeWerkstueck() = 0;
	virtual void schreibeSignale() = 0;
	virtual void transitionenAusfuehren() = 0;
};

#endif
