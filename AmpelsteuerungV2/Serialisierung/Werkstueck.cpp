#include <Werkstueck.h>

Werkstueck::Werkstueck() {
	id = next_id;
	next_id++;
}

Werkstueck::~Werkstueck() {

}

void setBohrung(bool bohrung){
	Werkstueck::bohrung = bohrung;
}

void Werkstueck::setMetall(bool metall){
	Werkstueck::metall = metall;
}

bool Wekstueck::getBohrung(){
	return bohrung;
}

bool Werkstueck::getMetall(){
	return metall;
}
