#pragma once
#include "service.h"
#include "oferta.h"

class ConsolUI {
	service& ctr;
	/*
	Citeste datele de la tastatura si adauga Pet
	arunca exceptie daca: nu se poate salva, nu e valid
	*/
	void adaugaUI();

	/*
	Citeste datele de la tastatura si modifica o oferta
	arunca exceptie daca: nu exista, nu e valid
	*/
	void modificareUI();

	/*
	Citeste datele de la tastatura si sterge o oferta
	arunca exceptie daca: nu exista
	*/
	void stergereUI();

	/*
	cauta o oferta
	arunca exceptie daca: nu se gaseste
	*/
	void cautareUI();

	/*
	Citeste datele de la tastatura si sterge o oferta
	arunca exceptie daca: nu exista
	*/
	void filtrarePretUI();

	/*
	executa raportul tipurilor de oferte din lista
	arunca exceptie daca: nu se gaseste
	*/
	void raportUI();

	/*
	citeste de la tastatura un numar de tip double
	*/
	double read_input();

	/*
	Tipareste o lista de animale la consola
	*/
	void tipareste(const vector<oferta>& oferte);

	/*
	tipareste cosul
	*/
	void tiparesteW(const vector<oferta>& oferte);

	/*
	creaza o lista random de elemente in wishlist
	*/
	void random();

	/*
	adauga o oferta in wishlist
	*/
	void adaugaWish();

	/*
	aterge un element din lista prin numarul lui de ordin
	*/
	void stergeWish();

	/*
	exporta intr-un fisier lista
	*/
	void exporta();
public:
	ConsolUI(service& ctr) noexcept :ctr{ ctr } {
	}
	//nu permitem copierea obiectelor
	ConsolUI(const ConsolUI& ot) = delete;

	void start();
};