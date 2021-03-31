#pragma once 
#include <string>
#include <iostream>

using namespace std;

class oferta {
	std::string des;
	std::string den;
	std::string tip;
	double pret;
public:
	oferta(const string den, const string des, const string tip, double pret) :den{ den }, des{ des }, tip{ tip }, pret{ pret }{}

	oferta() = default;

	/*
	oferta(const oferta& ot) :den{ ot.den }, des{ ot.des }, tip{ ot.tip }, pret{ ot.pret }{
		cout << "!!!!!!!!!\n";
	}
	*/

	string getDenumire() const {
		return den;
	}

	string getDestinatie() const {
		return des;
	}

	string getTip() const {
		return tip;
	}

	double getPret() const noexcept {
		return pret;
	}
};

/*
Compara dupa denumire
returneaza true daca o1.tip e mai mic decat o2.tip
*/
bool cmpDenumire(const oferta& o1, const oferta& o2);

/*
Compara dupa denumire
returneaza true daca o1.tip e mai mare decat o2.tip
*/
bool cmpDenumireD(const oferta& o1, const oferta& o2);

/*
Compara dupa destinatie
returneaza true daca o1.destinatie e mai mic decat o2.destinatie
*/
bool cmpDestinatie(const oferta& o1, const oferta& o2);

/*
Compara dupa destinatie
returneaza true daca o1.destinatie e mai mare decat o2.destinatie
*/
bool cmpDestinatieD(const oferta& o1, const oferta& o2);

/*
Compara dupa tip
returneaza true daca o1.tip e mai mic decat o2.tip
*/
bool cmpTip(const oferta& o1, const oferta& o2);

/*
Compara dupa tip
returneaza true daca o1.tip e mai mare decat o2.tip
*/
bool cmpTipD(const oferta& o1, const oferta& o2);

/*
Compara dupa pret
returneaza true daca o1.pret e mai mic decat o2.pret
*/
bool cmpPret(const oferta& o1, const oferta& o2) noexcept;

/*
Compara dupa pret
returneaza true daca o1.pret e mai mare decat o2.pret
*/
bool cmpPretD(const oferta& o1, const oferta& o2) noexcept;
