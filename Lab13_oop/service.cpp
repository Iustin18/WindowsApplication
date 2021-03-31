#include "service.h"

#include<functional>
#include <algorithm>
#include <assert.h>
#include <map>
#include <unordered_map>
#include <iostream>
#include <numeric>
#include <sstream>

vector<oferta> service::generalsort(bool(*maiMicF)(const oferta&, const oferta&)) {
	vector<oferta> v = { rep.getAll() };
	if (maiMicF != nullptr) {
		std::sort(v.begin(), v.end(), [maiMicF](const oferta& o1, const oferta& o2) {return maiMicF(o1, o2); });
		/*
		for (size_t i = 0; i < v.size(); i++) {
			for (size_t j = i + 1; j < v.size(); j++) {
				if (!maiMicF(v[i], v[j])) {
					oferta aux = v[i];
					v[i] = v[j];
					v[j] = aux;
				}
			}
		}
		*/
	}
	return v;
}

void service::raport(vector<DTO>& out) {
	auto l = getAll();
	map<string, DTO> output;
	for (auto item : l) {
		if (output.find(item.getTip()) == output.end()) {
			DTO act{};
			act.tip = item.getTip();
			act.count = 0;
			output.insert(pair<string, DTO>(item.getTip(), act));
		}
		output[item.getTip()].count++;
	}
	for (auto item : l) {
		DTO act{};
		act.count = output[item.getTip()].count;
		act.denumire = item.getDenumire();
		act.tip = item.getTip();
		out.push_back(act);
	}
}

void service::addOferta(const string& den, const string& des, const string& tip, double pret) {
	oferta o{ den,des,tip,pret };
	val.validate(o);
	rep.store(o);
	undoActions.push_back(std::make_unique<undoAdauga>(rep, o.getDenumire()));
}

void service::modOferta(string denumire, const string& den, const string& des, const string& tip, double pret) {
	oferta o{ den,des,tip,pret };
	vector<oferta> l = getAll();
	oferta o2 = rep.find(denumire);
	val.validate(o);
	rep.mod(denumire, o);
	undoActions.push_back(std::make_unique<undoModifica>(rep, den, o2));
}

void service::stergere(string denumire) {
	oferta o = rep.find(denumire);
	rep.delet(denumire);
	undoActions.push_back(std::make_unique<undoStergere>(rep, o));
}

const oferta& service::cautare(const string denumire) {
	return rep.find(denumire);
}

vector<oferta> service::sortByDenumire() {
	return generalsort(cmpDenumire);
}

vector<oferta> service::sortByDenumireD() {
	return generalsort(cmpDenumireD);
}

vector<oferta> service::sortByDestinatie() {
	return generalsort(cmpDestinatie);
}

vector<oferta> service::sortByDestinatieD() {
	return generalsort(cmpDestinatieD);
}

vector<oferta> service::sortByTip() {
	return generalsort(cmpTip);
}

vector<oferta> service::sortByTipD() {
	return generalsort(cmpTipD);
}

vector<oferta> service::sortByPret() {
	return generalsort(cmpPret);
}

vector<oferta> service::sortByPretD() {
	return generalsort(cmpPretD);
}

vector<oferta> service::sortByTipPret() {
	return generalsort([](const oferta& o1, const oferta& o2) {
		if (o1.getTip() == o2.getTip()) {
			return o1.getPret() < o2.getPret();
		}
		return o1.getTip() < o2.getTip();
		});
}

vector<oferta> service::sortByTipPretD() {
	return generalsort([](const oferta& o1, const oferta& o2) {
		if (o1.getTip() == o2.getTip()) {
			return o1.getPret() > o2.getPret();
		}
		return o1.getTip() > o2.getTip();
		});
}

vector<oferta> service::filtreaza(function<bool(const oferta&)> fct) {
	vector<oferta> rez;
	for (const auto& oferta : rep.getAll()) {
		if (fct(oferta)) {
			rez.push_back(oferta);
		}
	}
	return rez;
}

vector<oferta> service::filtrarePretMaiMic(double pret) {
	return filtreaza([pret](const oferta& o) {
		return o.getPret() < pret;
		});
}

vector<oferta> service::filtrarePret(double pretMin, double pretMax) {
	return filtreaza([=](const oferta& o) {
		return o.getPret() >= pretMin && o.getPret() <= pretMax;
		});
}

vector<oferta> service::filtrareDestinatie(string destinatie) {
	vector<oferta> rez;
	for (const auto& oferta : rep.getAll()) {
		if (oferta.getDestinatie() == destinatie) {
			rez.push_back(oferta);
		}
	}
	return rez;
}

void service::randomServ(int nr) {
	wish.randomRep(getAll(), nr);
	notify();
}

void service::goleste() {
	wish.golesteRep();
	notify();
}

void service::adaugaWish(const int id) {
	wish.adaugaWishlist(getAll(), id);
	undoActionsWish.push_back(std::make_unique<undoAdaugaWish>(wish, wish.getAllW().size() - 1));
	notify();
}

void service::stergeWish(const int nr) {
	wish.stergeWish(nr);
	notify();
}

auto op_suma(oferta o1) {
	return o1.getPret();
}

double op_suma2(double x, double y) {
	return x + y;
}

double service::suma() {
	vector<oferta> l = getAll();
	vector<double> sum;
	std::transform(l.begin(), l.end(), back_inserter(sum), op_suma);
	return std::accumulate(sum.begin(), sum.end(), 0.0, op_suma2);
}

void service::undo() {
	if (undoActions.empty()) {
		throw ofertaRepoException{ "Nu mai exista operatii" };
	}
	undoActions.back()->doUndo();
	undoActions.pop_back();
}

void service::undoWish() {
	if (undoActionsWish.empty()) {
		throw ofertaRepoException{ "Nu mai exista operatii" };
	}
	undoActionsWish.back()->doUndoWish();
	undoActionsWish.pop_back();
	notify();
}


void testAdaugareS() {
	repository rep;
	ofertaValidator val;
	repositoryW wish;
	service ctr{ rep,val,wish };
	ctr.addOferta("a", "a", "a", 4);
	assert(ctr.getAll().size() == 1);

	ctr.undo();
	assert(ctr.getAll().size() == 0);

	try {
		ctr.addOferta("", "", "", -1);
		assert(false);
	}
	catch (ValidateException&) {
		assert(true);
	}

	try {
		ctr.addOferta("a", "a", "a", -1);
		assert(false);
	}
	catch (ValidateException&) {
		assert(true);
	}
}

void testModifica() {
	repository rep;
	ofertaValidator val;
	repositoryW wish;
	service ctr{ rep,val,wish };
	string s;
	ctr.addOferta("a", "a", "a", 6);
	auto l = rep.getAll();
	assert(l.size() == 1);
	s = l.at(0).getDenumire();
	assert(s == "a");
	assert(l.at(0).getDestinatie() == "a");
	assert(l.at(0).getTip() == "a");
	assert(l.at(0).getPret() == 6);
	ctr.modOferta("a", "b", "c", "d", 45);
	l = rep.getAll();
	assert(l.size() == 1);
	assert(l.at(0).getDenumire() == "b");
	assert(l.at(0).getDestinatie() == "c");
	assert(l.at(0).getTip() == "d");
	assert(l.at(0).getPret() == 45);

	ctr.undo();
	l = rep.getAll();
	assert(l.at(0).getDenumire() == "a");

	try {
		ctr.modOferta("c", "b", "c", "d", 45);
		assert(false);
	}
	catch (ofertaRepoException) {
		assert(true);
	}
}

void testDeletCauta() {
	repository rep;
	ofertaValidator val;
	repositoryW wish;
	service ctr{ rep,val,wish };
	ctr.addOferta("a", "a", "a", 6);
	ctr.addOferta("b", "b", "b", 60);
	ctr.addOferta("c", "c", "c", 600);
	auto l = rep.getAll();
	assert(l.size() == 3);
	ctr.stergere("a");
	l = rep.getAll();
	assert(l.size() == 2);

	ctr.undo();
	l = rep.getAll();
	assert(l.size() == 3);

	try {
		ctr.stergere("g");
		assert(false);
	}
	catch (const ofertaRepoException & ex) {
		assert(true);
		stringstream ss;
		ss << ex;
		assert(ss.str().find("exista") >= 0);
	}

	try {
		auto o = ctr.cautare("a");
		assert(true);
	}
	catch (ofertaRepoException) {
		assert(false);
	}
}

void testFiltrare() {
	repository rep;
	ofertaValidator val;
	repositoryW wish;
	service ctr{ rep,val,wish };
	ctr.addOferta("a", "a", "a", 6);
	ctr.addOferta("b", "b", "b", 60);
	ctr.addOferta("c", "c", "c", 600);
	assert(ctr.filtrarePret(6, 70).size() == 2);
	assert(ctr.filtrarePret(6, 60).size() == 2);
	assert(ctr.filtrarePretMaiMic(60).size() == 1);
	assert(ctr.filtrarePretMaiMic(7).size() == 1);
	assert(ctr.filtrarePretMaiMic(6).size() == 0);
	assert(ctr.filtrareDestinatie("a").size() == 1);
	assert(ctr.filtrareDestinatie("z").size() == 0);
}

void testSortare() {
	repository rep;
	ofertaValidator val;
	repositoryW wish;
	service ctr{ rep,val,wish };

	ctr.addOferta("z", "z", "z", 6);
	ctr.addOferta("b", "a", "a", 60);
	ctr.addOferta("c", "b", "a", 600);

	auto firstO = ctr.sortByDenumire();
	assert(firstO.at(0).getDenumire() == "b");

	firstO = ctr.sortByDenumireD();
	assert(firstO.at(0).getDenumire() == "z");

	firstO = ctr.sortByTipPret();
	assert(firstO.at(0).getPret() == 60);

	firstO = ctr.sortByTipPretD();
	assert(firstO.at(0).getPret() == 6);

	firstO = ctr.sortByDestinatie();
	assert(firstO.at(0).getDestinatie() == "a");

	firstO = ctr.sortByDestinatieD();
	assert(firstO.at(0).getDestinatie() == "z");

	firstO = ctr.sortByTip();
	assert(firstO.at(0).getTip() == "a");

	firstO = ctr.sortByTipD();
	assert(firstO.at(0).getTip() == "z");

	firstO = ctr.sortByPret();
	assert(firstO.at(0).getPret() == 6);

	firstO = ctr.sortByPretD();
	assert(firstO.at(0).getPret() == 600);
}

void testRapWish() {
	repository rep;
	ofertaValidator val;
	repositoryW wish;
	service ctr{ rep,val,wish };

	ctr.addOferta("z", "z", "z", 6);
	ctr.addOferta("b", "a", "a", 60);
	ctr.addOferta("c", "b", "a", 600);

	vector<DTO> l;
	ctr.raport(l);
	assert(l.size() == 3);
	assert(l.at(1).count == 2);
	ctr.randomServ(20);
	assert(ctr.getAllW().size() == 20);

	ctr.goleste();
	assert(ctr.getAllW().size() == 0);

	ctr.adaugaWish(2);
	assert(ctr.getAllW().size() == 1);

	ctr.stergeWish(0);
	assert(ctr.getAllW().size() == 0);

	ctr.adaugaWish(2);
	assert(ctr.getAllW().size() == 1);

	ctr.undoWish();
	assert(ctr.getAllW().size() == 0);

}

void testSuma() {
	repository rep;
	ofertaValidator val;
	repositoryW wish;
	service ctr{ rep,val,wish };

	ctr.addOferta("z", "z", "z", 6);
	ctr.addOferta("b", "a", "a", 70.1);
	ctr.addOferta("c", "b", "a", 310);

	assert(ctr.suma() == 386.1);
}

void testService() {
	testAdaugareS();
	testModifica();
	testDeletCauta();
	testFiltrare();
	testSortare();
	testRapWish();
	testSuma();
}