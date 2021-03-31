#pragma once
#include "oferta.h"
#include "wishlist.h"

class ActiuneUndoWish {
public:
	virtual void doUndoWish() = 0;
	virtual ~ActiuneUndoWish() = default;
};

class undoAdaugaWish :public ActiuneUndoWish {
	int id;
	repositoryW& wish;
public:
	undoAdaugaWish(repositoryW& rep, const int id) :wish{ rep }, id{ id }{}

	void doUndoWish() override {
		wish.stergeWish(id);
	}
};