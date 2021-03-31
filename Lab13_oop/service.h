#pragma once

#include "oferta.h"
#include "repository.h"
#include "wishlist.h"
#include "dto.h"
#include "Observator.h"
#include <string>
#include <vector>

#include <functional>
#include "validator.h"

#include "undo.h"
#include "undoWish.h"

using std::vector;
using std::function;
using std::string;
using std::unique_ptr;

class service : public Observable {
	repo& rep;
	ofertaValidator& val;
	repositoryW& wish;

	std::vector<unique_ptr<ActiuneUndo>> undoActions;

	std::vector<unique_ptr<ActiuneUndoWish>> undoActionsWish;
	/*
	 Functie de sortare generala
	 maiMareF - functie care compara 2 oferte, verifica daca are loc relatia mai mare
			  - poate fi orice functie (in afara clasei) care respecta signatura (returneaza bool are 2 parametrii oferta)
			  - poate fi functie lambda (care nu capteaza nimic in capture list)
	 returneaza o lista sortata dupa criteriu dat ca paramatru
	*/
	vector<oferta> generalsort(bool (*maiMicF)(const oferta&, const oferta&));

	/*
	Functie generala de filtrare
	fct - poate fi o functie
	fct - poate fi lambda, am folosit function<> pentru a permite si functii lambda care au ceva in capture list
	returneaza doar oferte care trec de filtru (fct(pet)==true)
	*/
	vector<oferta> filtreaza(function<bool(const oferta&)>fct);
public:
	service(repo& rep, ofertaValidator& val, repositoryW& wish) noexcept :rep{ rep }, val{ val }, wish{ wish }{}
	//nu permitem copierea de obiecte service
	service(const service& ot) = delete;

	/*
	 returneaza toate ofertele in ordinea in care au fost adaugate
	*/
	vector<oferta> getAll() {
		return rep.getAll();
	}

	/*
	 returneaza toate ofertele in ordinea in care au fost adaugate
	*/
	const vector<oferta>& getAllW() noexcept {
		return wish.getAllW();
	}

	/*
	Adauga o noua oferta
	arunca exceptie daca: nu se poate salva, nu este valid
	*/
	void addOferta(const string& den, const string& des, const string& tip, double pret);

	/*
	Modifica o oferta
	arunca exceptie daca: nu exista oferta, nu este valid
	*/
	void modOferta(string denumire, const string& den, const string& des, const string& tip, double pret);

	/*
	Sterge o oferta
	arunca exceptie daca: nu exista oferta
	*/
	void stergere(string denumire);

	/*
	Cauta o oferta
	arunca exceptie daca nu exista oferta
	daca exista returneaza oferta
	*/
	const oferta& cautare(const string denumire);

	/*
	Sorteaza dupa denumire
	*/
	vector<oferta> sortByDenumire();

	/*
	sorteaza dupa denumire descrescator
	*/
	vector<oferta> sortByDenumireD();

	/*
	Sorteaza dupa destinatie
	*/
	vector<oferta> sortByDestinatie();

	/*
	sorteaza dupa destinatie descrescator
	*/
	vector<oferta> sortByDestinatieD();

	/*
	Sorteaza dupa tip
	*/
	vector<oferta> sortByTip();

	/*
	sorteaza dupa tip descrescator
	*/
	vector<oferta> sortByTipD();

	/*
	Sorteaza dupa pret
	*/
	vector<oferta> sortByPret();

	/*
	sorteaza dupa pret ddescrescator
	*/
	vector<oferta> sortByPretD();

	/*
	Sorteaza dupa tip si pret
	*/
	vector<oferta> sortByTipPret();

	/*
	Sorteaza dupa tip si pret descrescator
	*/
	vector<oferta> sortByTipPretD();

	/*
	returneaza doar ofertele cu pret mai mic decat cel dat
	*/
	vector<oferta> filtrarePretMaiMic(double pret);

	/*
	returneaza doar ofertele cu pret intre cele doua preturi
	*/
	vector<oferta> filtrarePret(double pretMin, double pretMax);

	/*
	returneaza doar ofertele cu destinatia data
	*/
	vector<oferta> filtrareDestinatie(string destinatie);

	/*
	executa un raport a listei dupa tip
	*/
	void raport(vector<DTO>& out);

	/*
	adauga in wishlist un numar nr de oferte random
	*/
	void randomServ(int nr);

	/*
	goleste wishlist adica sterge toate ofertele
	*/
	void goleste();

	/*
	adauga o oferta in wishlist
	*/
	void adaugaWish(const int id);

	/*
	aterge un element din lista prin numarul lui de ordin
	*/
	void stergeWish(const int nr);

	/*
	suma pretului ofertelor prezente
	*/
	double suma();

	/*
	executa undo pentru adauga, stergere si modifica
	*/
	void undo();

	/*
	executa undo pentru adauga in wishlist
	*/
	void undoWish();
};

void testService();