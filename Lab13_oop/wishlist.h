#pragma once
#include "oferta.h"
#include "repository.h"

#include <vector>
#include <string>
#include <ostream>

using std::vector;
using std::string;
using std::ostream;

class repositoryW {
	vector<oferta> wishlist;

public:
	repositoryW() = default;
	//nu permitem copierea de obiecte
	repositoryW(const repositoryW& ot) = delete;

	/*
	returneaza toate ofertele salvate
	*/
	const vector<oferta>& getAllW() const noexcept;

	/*
	sterge toate elementele din wishlist
	*/
	void golesteRep();

	/*
	adauga random in lista niste oferte
	*/
	void randomRep(vector<oferta> l, int nr);

	/*
	adauga o oferta in wishlist
	*/
	void adaugaWishlist(vector<oferta> l, const int id);

	/*
	aterge un element din lista prin numarul lui de ordin
	*/
	void stergeWish(const int nr);
};




/*
Folosit pentru a semnala situatii exceptionale care pot aparea in repo
*/
class ofertaWishException {
	string msg;
public:
	ofertaWishException(string m) :msg{ m } {}
	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const ofertaWishException& ex);
};

ostream& operator<<(ostream& out, const ofertaWishException& ex);

void testWish();
