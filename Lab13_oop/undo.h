#pragma once
#include "oferta.h"
#include "repository.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class undoAdauga :public ActiuneUndo {
	string denumire;
	repo& rep;
public:
	undoAdauga(repo& rep, const string denumire) :rep{ rep }, denumire{ denumire }{}

	void doUndo() override {
		rep.delet(denumire);
	}
};

class undoStergere : public ActiuneUndo {
	oferta ofertaSters;
	repo& rep;
public:
	undoStergere(repo& rep, const oferta& o) :rep{ rep }, ofertaSters{ o }{}

	void doUndo() override {
		rep.store(ofertaSters);
	}
};

class undoModifica : public ActiuneUndo {
	string denumire;
	oferta ofertaModificata;
	repo& rep;
public:
	undoModifica(repo& rep, const string denumire, const oferta& o) :rep{ rep }, denumire{ denumire }, ofertaModificata{ o }{}

	void doUndo() override {
		rep.mod(denumire, ofertaModificata);
	}
};