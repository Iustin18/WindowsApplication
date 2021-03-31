#include "wishlist.h"
#include <assert.h>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <random>

using std::ostream;
using std::stringstream;
using std::vector;

void repositoryW::golesteRep() {
	vector<oferta> lista;
	wishlist = lista;
}

const vector<oferta>& repositoryW::getAllW() const noexcept {
	return wishlist;
}

void repositoryW::randomRep(vector<oferta> l, int nr) {
	if (nr <= 0) {
		throw ofertaWishException("Trebuie un numar positiv positiv! \n");
	}
	else {
		while (nr > 0) {
			std::mt19937 mt{ std::random_device{}() };
			std::uniform_int_distribution<> const dist(0, l.size() - 1);
			const int rand = dist(mt);
			wishlist.push_back(l.at(rand));
			nr--;
		}
	}
}

void repositoryW::adaugaWishlist(vector<oferta> l, const int id) {
	if ((size_t)id < l.size()) {
		wishlist.push_back(l.at(id));
	}
	else {
		throw ofertaWishException("Nu exista aceasta oferta! \n");
	}
}

void repositoryW::stergeWish(const int nr) {
	auto l = getAllW().size();
	if ((size_t)nr < l) {
		wishlist.erase(wishlist.begin() + nr);
	}
	else {
		throw ofertaWishException("Nu exista aceasta oferta! \n");
	}
}

ostream& operator<<(ostream& out, const ofertaWishException& ex) {
	out << ex.msg;
	return out;
}

void testWish() {
	repositoryW rep;
	vector<oferta> l;
	l.push_back(oferta{ "a","a","a",10 });
	l.push_back(oferta{ "ba","b","b",54 });
	l.push_back(oferta{ "c","cc","fr",64.7 });
	l.push_back(oferta{ "z","zz","br",100 });

	try {
		rep.randomRep(l, -8);
		assert(false);
	}
	catch (const ofertaWishException & ex) {
		assert(true);
		stringstream ss;
		ss << ex;
		assert(ss.str().find("positiv") >= 0);
	}

	rep.randomRep(l, 20);
	assert(rep.getAllW().size() == 20);

	rep.golesteRep();
	assert(rep.getAllW().size() == 0);

	rep.adaugaWishlist(l, 1);
	assert(rep.getAllW().size() == 1);

	try {
		rep.adaugaWishlist(l, -8);
		assert(false);
	}
	catch (const ofertaWishException & ex) {
		assert(true);
		stringstream ss;
		ss << ex;
		assert(ss.str().find("exista") >= 0);
	}

	try {
		rep.stergeWish(30);
		assert(false);
	}
	catch (const ofertaWishException & ex) {
		assert(true);
		stringstream ss;
		ss << ex;
		assert(ss.str().find("exista") >= 0);
	}
}