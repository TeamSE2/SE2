#ifndef
#define WERKSTUECK

class Werkstueck{
private:
	static next_id = 0
	int id;
	bool bohrung;
	bool metall;

public:
	Werkstueck(bool bohrung, bool metall);
	~Werkstueck();

	void setBohrung(bool bohrung);
	void setMetall(bool Metall);
	bool getBohrung();
	bool getMetall();
};

#endif WERKSTUECK
