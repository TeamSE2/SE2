#ifndef SERIELL
#define SERIELL

class Seriell{
private:

public:
	Seriell();
	~Seriell();
	bool leseObject(string pfad, T *object);
	bool schreibeObject(string pfad, T *object);


};

#endif

