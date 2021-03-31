#pragma once
#include "oferta.h"

#include <vector>
#include <string>
#include <ostream>
#include <map>
#include <unordered_map>
#include <time.h>
#include <stdlib.h>

using std::vector;
using std::string;
using std::ostream;

class repo {
public:
	virtual bool exist(const oferta& o) = 0;

	virtual void store(const oferta& o) = 0;

	virtual void mod(string denumire, const oferta& o) = 0;

	virtual void delet(string denumire) = 0;

	virtual const oferta& find(string denumire) = 0;

	virtual vector<oferta> getAll() = 0;
};

class repository : public repo {
	/*
	vector<oferta> all;
	*/

	map<string, oferta> all;

	/*
	metoda privata verifica daca exista deja o in repository
	*/
	bool exist(const oferta& o) override;
public:
	repository() = default;
	//nu permitem copierea de obiecte
	repository(const repository& ot) = delete;

	/*
	Salvare oferta
	arunca exceptie daca mai exista o oferta identica
	*/
	void store(const oferta& o) override;

	/*
	modifica o oferta
	arunca exceptie daca oferta indicata prin id nu exista
	*/
	void mod(string denumire, const oferta& o) override;

	/*
	sterge o oferta
	arunca exceptie daca oferta indicata de id nu exista
	*/
	void delet(string denumire) override;

	/*
	Cauta
	arunca exceptie daca nu exista oferta
	*/
	const oferta& find(string denumire) override;

	/*
	returneaza toate ofertele salvate
	*/
	vector<oferta> getAll() override;
};

/*
Folosit pentru a semnala situatii exceptionale care pot aparea in repo
*/
class ofertaRepoException {
	string msg;
public:
	ofertaRepoException(string m) :msg{ m } {}
	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const ofertaRepoException& ex);
};

ostream& operator<<(ostream& out, const ofertaRepoException& ex);

class repositoryFile : public repo {
private:
	std::string fName;
	void loadFromFile();
	void writeToFile();

	map<string, oferta> all;

	/*
	metoda privata verifica daca exista deja o in repository
	*/
	bool exist(const oferta& o) override;
public:
	repositoryFile(std::string fName) : fName{ fName } {
		loadFromFile();
	}

	/*
	Salvare oferta
	arunca exceptie daca mai exista o oferta identica
	*/
	void store(const oferta& o) override;

	/*
	modifica o oferta
	arunca exceptie daca oferta indicata prin id nu exista
	*/
	void mod(string denumire, const oferta& o) override;

	/*
	sterge o oferta
	arunca exceptie daca oferta indicata de id nu exista
	*/
	void delet(string denumire) override;

	/*
	Cauta
	arunca exceptie daca nu exista oferta
	*/
	const oferta& find(string denumire) override;

	/*
	returneaza toate ofertele salvate
	*/
	vector<oferta> getAll() override;
};

class repoNou : public repo {
private:
	float procent;

	map<string, oferta> all;

	/*
	metoda privata verifica daca exista deja o in repository
	*/
	bool exist(const oferta& o) override;

public:
	repoNou(float proc) : procent{ proc } {
		procent = procent * 100;
		srand(static_cast<unsigned int>(time(nullptr)));
		if (rand() % 20 >= procent) throw ofertaRepoException("Probabilitate!");
	}

	/*
	Salvare oferta
	arunca exceptie daca mai exista o oferta identica
	*/
	void store(const oferta& o) override;

	/*
	modifica o oferta
	arunca exceptie daca oferta indicata prin id nu exista
	*/
	void mod(string denumire, const oferta& o) override;

	/*
	sterge o oferta
	arunca exceptie daca oferta indicata de id nu exista
	*/
	void delet(string denumire) override;

	/*
	Cauta
	arunca exceptie daca nu exista oferta
	*/
	const oferta& find(string denumire) override;

	/*
	returneaza toate ofertele salvate
	*/
	vector<oferta> getAll() override;
};


void testeRepo();