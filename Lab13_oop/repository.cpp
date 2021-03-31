#include "repository.h"
#include <assert.h>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <random>
#include <fstream>

using std::ostream;
using std::stringstream;
using std::vector;

void repository::store(const oferta& o) {
	if (exist(o)) {
		throw ofertaRepoException("Exista deja oferta denumire: " + o.getDenumire());
	}
	else {
		this->all.insert({ o.getDenumire(),o });
	}
}

void repository::mod(string denumire, const oferta& o) {
	int gasit = 0;
	for (auto oferta : getAll()) {
		if (oferta.getDenumire() == denumire) {
			gasit = 1;
			break;
		}
	}
	if (gasit == 1) {
		all.erase(denumire);
		store(o);
	}
	else {
		throw ofertaRepoException("Nu exista aceasta oferta: ");
	}
}

void repository::delet(string denumire) {
	int gasit = 0;
	for (auto oferta : getAll()) {
		if (oferta.getDenumire() == denumire) {
			gasit = 1;
			break;
		}
	}
	if (gasit == 1) {
		all.erase(denumire);
	}
	else {
		throw ofertaRepoException("NU exista oferta denumire:");
	}
}

bool repository::exist(const oferta& o) {
	try {
		find(o.getDenumire());
		return true;
	}
	catch (ofertaRepoException&) {
		return false;
	}
}

const oferta& repository::find(string denumire) {
	auto rez = std::find_if(all.begin(), all.end(), [denumire](const pair<string, oferta> o) {
		if (o.second.getDenumire() == denumire) return true;
		else return false;
		});
	if (rez != all.end()) {
		return rez->second;
	}
	else {
		throw ofertaRepoException("nu exista o oferta numarul:" + denumire);
	}


	/*
	for (const auto& o : all) {
		if (o.getDenumire() == denumire && o.getDestinatie() == destinatie && o.getTip()==tip && o.getPret()==pret) {
			return o;
		}
	}
	throw ofertaRepoException("nu exista o oferta:" + denumire);
	*/
}

auto op_transf(pair<string, oferta> o) {
	return o.second;
}

vector<oferta> repository::getAll() {
	vector<oferta> rez;
	std::transform(all.begin(), all.end(), back_inserter(rez), op_transf);
	return rez;
}

ostream& operator<<(ostream& out, const ofertaRepoException& ex) {
	out << ex.msg;
	return out;
}

void repositoryFile::loadFromFile() {
	std::ifstream in(fName);
	if (!in.is_open()) {
		throw ofertaRepoException("Nu se poate deschide fisierul: " + fName);
	}
	while (!in.eof()) {
		std::string denumire;
		in >> denumire;
		std::string destinatie;
		in >> destinatie;
		std::string tip;
		in >> tip;

		double pret;
		in >> pret;
		if (in.eof()) {
			break;
		}
		oferta o{ denumire.c_str(),destinatie.c_str(),tip.c_str(),pret };
		store(o);
	}
	in.close();
}

void repositoryFile::writeToFile() {
	std::ofstream out(fName);
	if (!out.is_open()) {
		throw ofertaRepoException("Nu se poate deschide fisierul: " + fName);
	}
	vector<oferta> l = getAll();
	for (auto o : l) {
		out << o.getDenumire() << ' ' << o.getDestinatie() << ' ' << o.getTip() << ' ' << o.getPret() << '\n';
	}
	out.close();
}

void repositoryFile::store(const oferta& o) {
	if (exist(o)) {
		throw ofertaRepoException("Exista deja oferta denumire: " + o.getDenumire());
	}
	else {
		this->all.insert({ o.getDenumire(),o });
	}
	writeToFile();
}

void repositoryFile::mod(string denumire, const oferta& o) {
	int gasit = 0;
	for (auto oferta : getAll()) {
		if (oferta.getDenumire() == denumire) {
			gasit = 1;
			break;
		}
	}
	if (gasit == 1) {
		all.erase(denumire);
		store(o);
	}
	else {
		throw ofertaRepoException("Nu exista aceasta oferta: ");
	}
	writeToFile();
}

void repositoryFile::delet(string denumire) {
	int gasit = 0;
	for (auto oferta : getAll()) {
		if (oferta.getDenumire() == denumire) {
			gasit = 1;
			break;
		}
	}
	if (gasit == 1) {
		all.erase(denumire);
	}
	else {
		throw ofertaRepoException("NU exista oferta denumire:");
	}
	writeToFile();
}

bool repositoryFile::exist(const oferta& o) {
	try {
		find(o.getDenumire());
		return true;
	}
	catch (ofertaRepoException&) {
		return false;
	}
}

const oferta& repositoryFile::find(string denumire) {
	auto rez = std::find_if(all.begin(), all.end(), [denumire](const pair<string, oferta> o) {
		if (o.second.getDenumire() == denumire) return true;
		else return false;
		});
	if (rez != all.end()) {
		return rez->second;
	}
	else {
		throw ofertaRepoException("nu exista o oferta:" + denumire);
	}
}

vector<oferta> repositoryFile::getAll() {
	vector<oferta> rez;
	std::transform(all.begin(), all.end(), back_inserter(rez), op_transf);
	return rez;
}


///////////////////////////////////////////////////////

void repoNou::store(const oferta& o) {
	if (rand() % 100 >= procent) throw ofertaRepoException("Probabilitate!");

	if (exist(o)) {
		throw ofertaRepoException("Exista deja oferta denumire: " + o.getDenumire());
	}
	else {
		this->all.insert({ o.getDenumire(),o });
	}
}

void repoNou::mod(string denumire, const oferta& o) {
	if (rand() % 100 >= procent) throw ofertaRepoException("Probabilitate!");

	int gasit = 0;
	for (auto oferta : getAll()) {
		if (oferta.getDenumire() == denumire) {
			gasit = 1;
			break;
		}
	}
	if (gasit == 1) {
		all.erase(denumire);
		store(o);
	}
	else {
		throw ofertaRepoException("Nu exista aceasta oferta: ");
	}
}

void repoNou::delet(string denumire) {
	if (rand() % 100 >= procent) throw ofertaRepoException("Probabilitate!");

	int gasit = 0;
	for (auto oferta : getAll()) {
		if (oferta.getDenumire() == denumire) {
			gasit = 1;
			break;
		}
	}
	if (gasit == 1) {
		all.erase(denumire);
	}
	else {
		throw ofertaRepoException("NU exista oferta denumire:");
	}
}

bool repoNou::exist(const oferta& o) {
	try {
		find(o.getDenumire());
		return true;
	}
	catch (ofertaRepoException&) {
		return false;
	}
}

const oferta& repoNou::find(string denumire) {
	auto rez = std::find_if(all.begin(), all.end(), [denumire](const pair<string, oferta> o) {
		if (o.second.getDenumire() == denumire) return true;
		else return false;
		});
	if (rez != all.end()) {
		return rez->second;
	}
	else {
		throw ofertaRepoException("nu exista o oferta numarul:" + denumire);
	}
}

vector<oferta> repoNou::getAll() {
	vector<oferta> rez;
	std::transform(all.begin(), all.end(), back_inserter(rez), op_transf);
	return rez;
}


void testAdaugare() {
	repository rep;
	rep.store(oferta{ "a","a","a",4 });
	assert(rep.getAll().size() == 1);
	assert(rep.find("a").getDenumire() == "a");
	rep.store(oferta{ "b","b","b",4 });
	assert(rep.getAll().size() == 2);

	try {
		rep.store(oferta{ "a","a","a",4 });
		assert(false);
	}
	catch (const ofertaRepoException & ex) {
		assert(true);
		stringstream ss;
		ss << ex;
		assert(ss.str().find("Exista") >= 0);
	}

	try {
		rep.delet("c");
		assert(false);
	}
	catch (const ofertaRepoException & ex) {
		assert(true);
		stringstream ss;
		ss << ex;
		assert(ss.str().find("exista") >= 0);
	}
}

void testCauta() {
	repository rep;
	rep.store(oferta{ "a","a","a",4 });
	rep.store(oferta{ "b","b","b",5 });

	auto o = rep.find("a");
	assert(o.getDenumire() == "a");
	assert(o.getDestinatie() == "a");
	assert(o.getTip() == "a");
	assert(o.getPret() == 4);

	try {
		rep.find("c");
		assert(false);
	}
	catch (const ofertaRepoException & ex) {
		assert(true);
		stringstream ss;
		ss << ex;
		assert(ss.str().find("exista") >= 0);
	}
}

void testFile() {
	repositoryFile rep{ "repoAux.txt" };
	rep.store(oferta{ "a","b","c",34 });
	assert(rep.getAll().size() == 2);
	rep.mod("a", oferta{ "fa","bd","cs",304 });
	assert(rep.getAll().at(1).getDenumire() == "fa");
	rep.delet("fa");
	assert(rep.getAll().size() == 1);
}

void testNou() {
	repoNou rep{ 1 };
	rep.store(oferta{ "a","b","c",34 });
	assert(rep.getAll().size() == 1);
	rep.mod("a", oferta{ "fa","bd","cs",304 });
	assert(rep.getAll().at(0).getDenumire() == "fa");
	rep.delet("fa");
	assert(rep.getAll().size() == 0);
}

void testeRepo() {
	testAdaugare();
	testCauta();
	testFile();
	testNou();
}