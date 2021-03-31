#include "console.h"

#include "oferta.h"
#include <iostream>
#include <string>
#include <fstream>

using std::cout;
using std::cin;
using std::string;

double ConsolUI::read_input() {
	double input = -1;
	bool valid = false;
	do {
		cin >> input;
		if (cin.good()) {
			valid = true;
		}
		else {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Nu este un numar!";
		}
	} while (!valid);
	return input;
}

void ConsolUI::tipareste(const vector<oferta>& oferte) {
	cout << "Ofertele:\n";
	int i = 0;
	for (const auto& oferta : oferte) {
		cout << i << ' ' << oferta.getDenumire() << ' ' << oferta.getDestinatie() << ' ' << oferta.getTip() << ' ' << oferta.getPret() << '\n';
		i++;
	}
	cout << "Sfarsit lista oferte\n";
}

void ConsolUI::tiparesteW(const vector<oferta>& oferte) {
	cout << "Ofertele:\n";
	int i = 0;
	for (const auto& oferta : oferte) {
		cout << i << oferta.getDenumire() << ' ' << oferta.getDestinatie() << ' ' << oferta.getTip() << ' ' << oferta.getPret() << '\n';
		i++;
	}
	cout << "Sfarsit lista oferte\n";
}

void ConsolUI::adaugaUI() {
	string den, des, tip;
	double pret;
	cout << "dati denumire:";
	cin >> den;
	cout << "dati destinatie:";
	cin >> des;
	cout << "dati tip:";
	cin >> tip;
	cout << "dati pret:";
	pret = read_input();
	ctr.addOferta(den, des, tip, pret);
	cout << "adaugat cu succes\n";
}

void ConsolUI::modificareUI() {
	string denumire, den, des, tip;
	double pret;

	cout << "dati denumirea curenta:";
	cin >> denumire;
	cout << "dati denumire:";
	cin >> den;
	cout << "dati destinatie:";
	cin >> des;
	cout << "dati tip:";
	cin >> tip;
	cout << "dati pret:";
	pret = read_input();
	ctr.modOferta(denumire, den, des, tip, pret);
	cout << "modificata cu succes\n";
}

void ConsolUI::stergereUI() {
	string denumire;
	cout << "dati denumirea: ";
	cin >> denumire;
	ctr.stergere(denumire);
	cout << "sters cu succes\n";
}

void ConsolUI::cautareUI() {
	string denumire;
	cout << "inserati denumire: ";
	cin >> denumire;
	const oferta& o = ctr.cautare(denumire);
	cout << "oferta: Denumire- " << o.getDenumire() << " Destinatie- " << o.getDestinatie() << " Tip- " + o.getTip() << " Pret- " << o.getPret() << '\n';
}

void ConsolUI::filtrarePretUI() {
	double pretMin, pretMax;
	cout << "Pretul minim: ";
	pretMin = read_input();
	cout << "Pretul maxim: ";
	pretMax = read_input();
	tipareste(ctr.filtrarePret(pretMin, pretMax));
}

void ConsolUI::raportUI() {
	vector<DTO> l;
	ctr.raport(l);
	for (auto item : l) {
		cout << item.denumire << " - Tip: " << item.tip << " (count=" << item.count << ")\n";
	}
}

void ConsolUI::random() {
	if (ctr.getAllW().size() != 0) {
		ctr.goleste();
	}
	int nr;
	cout << "NUmarul de elemente care doriti: ";
	nr = (int)read_input();
	ctr.randomServ(nr);
}

void ConsolUI::adaugaWish() {
	int id;
	cout << "Inserati numarul ofertei: ";
	id = (int)read_input();
	ctr.adaugaWish(id);
}

void ConsolUI::stergeWish() {
	int nr;
	cout << "inserati numarul ofertei de sters: ";
	nr = (int)read_input();
	ctr.stergeWish(nr);
}

void ConsolUI::exporta() {
	string den;
	cout << "Numele fisierului unde doriti sa exportati: ";
	cin >> den;
	auto l = ctr.getAllW();
	ofstream f(den);
	int i = 0;
	for (auto o : l) {
		f << i << ' ' << o.getDenumire() << ' ' << o.getDestinatie() << ' ' << o.getTip() << ' ' << o.getPret() << '\n';
		i++;
	}
	f.close();

}

void ConsolUI::start() {
	while (true) {
		cout << "Meniu:\n";
		cout << "1 adauga\n";
		cout << "2 tipareste\n";
		cout << "3 modifica\n";
		cout << "4 stergere\n";
		cout << "5 cautare\n";
		cout << "6 sorteaza denumire\n";
		cout << "7 sorteaza denumire descrescator\n";
		cout << "8 sorteaza destinatie\n";
		cout << "9 sorteaza destinatie descrescator\n";
		cout << "10 sorteaza tip\n";
		cout << "11 sorteaza tip descrescator\n";
		cout << "12 sorteaza pret\n";
		cout << "13 sorteaza pret descrescator\n";
		cout << "14 sorteaza tip si pret\n";
		cout << "15 sorteaza tip si pret descrescator\n";
		cout << "16 filtreaza pret\n";
		cout << "17 filtreaza pret min max\n";
		cout << "18 filtreaza destinatie\n";
		cout << "19 raport tip\n";
		cout << "20 random wishlist\n";
		cout << "21 afisare wishlist\n";
		cout << "22 goleste wishlist\n";
		cout << "23 adauga in wishlist\n";
		cout << "24 sterge din wishlist\n";
		cout << "25 exporta\n";
		cout << "26 suma\n";
		cout << "27 Undo\n";
		cout << "28 Undo Wish\n";
		cout << "0 Exit\n";
		cout << "\nNumarul de oferte in wishlist este: " << ctr.getAllW().size() << '\n';
		cout << "Comanda: ";
		int cmd;
		string den;
		cmd = (int)read_input();
		try {
			switch (cmd) {
			case 1:
				adaugaUI();
				break;
			case 2:
				tipareste(ctr.getAll());
				break;
			case 3:
				modificareUI();
				break;
			case 4:
				stergereUI();
				break;
			case 5:
				cautareUI();
				break;
			case 6:
				tipareste(ctr.sortByDenumire());
				break;
			case 7:
				tipareste(ctr.sortByDenumireD());
				break;
			case 8:
				tipareste(ctr.sortByDestinatie());
				break;
			case 9:
				tipareste(ctr.sortByDestinatieD());
				break;
			case 10:
				tipareste(ctr.sortByTip());
				break;
			case 11:
				tipareste(ctr.sortByTipD());
				break;
			case 12:
				tipareste(ctr.sortByPret());
				break;
			case 13:
				tipareste(ctr.sortByPretD());
				break;
			case 14:
				tipareste(ctr.sortByTipPret());
				break;
			case 15:
				tipareste(ctr.sortByTipPretD());
				break;
			case 16:
				cout << "Dati pret maxim: ";
				tipareste(ctr.filtrarePretMaiMic(read_input()));
				break;
			case 17:
				filtrarePretUI();
				break;
			case 18:
				cout << "Destinatie: ";
				cin >> den;
				tipareste(ctr.filtrareDestinatie(den));
				break;
			case 19:
				raportUI();
				break;
			case 20:
				random();
				break;
			case 21:
				tiparesteW(ctr.getAllW());
				break;
			case 22:
				ctr.goleste();
				break;
			case 23:
				adaugaWish();
				break;
			case 24:
				stergeWish();
				break;
			case 25:
				exporta();
				break;
			case 26:
				cout << "Suma este: " << ctr.suma() << '\n';
				break;
			case 27:
				ctr.undo();
				cout << "Undo executat cu succes! ";
				break;
			case 28:
				ctr.undoWish();
				cout << "Undo executat cu succes! ";
				break;
			case 0:
				cout << "Sfarsit!";
				return;
			default:
				cout << "Comanda invalida\n";
			}
		}
		catch (const ofertaRepoException & ex) {
			cout << ex << '\n';
		}
		catch (const ValidateException & ex) {
			cout << ex << '\n';
		}
		catch (const ofertaWishException & ex) {
			cout << ex << '\n';
		}
	}
}