#include <iostream>
#include <fstream>
#include <Seriell_io.h>

template <class T>
T Seriell_io::leseObject(String pfad, T *object){
	bool ok = false;

	ifstream datei(pfad);

	if(!datei){
		cerr << "Fehler beim Oeffnen der Datei"<< endl;
	}

	if(!datei.eof()){
		object = datei.read((char*) object, sizeof(object));
		ok = true;
	}else{
		cerr << "Ende der datei erreicht" << endl;
	}

	close(datei);

	return ok;
}

template <class T>
bool schreibeObject(string pfad, T *object){
	bool ok = false;

	ofstream datei(pfad);

	if(!datei){
		cerr << "Fehler beim Oeffnen der Datei"<< endl;
	}

	close(datei);

	return ok;
}
