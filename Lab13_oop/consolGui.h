#pragma once
#include "service.h"
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <Qtwidgets/qboxlayout.h>
#include <Qtwidgets/qlineedit.h>
#include <Qtwidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <qdebug.h>
#include <qmessagebox.h>
#include <vector>
#include <sstream>

using std::vector;

class consolGui : public QWidget {
public:
	service& ctr;

	consolGui(service& ctr) noexcept :ctr{ ctr } {
		loadData();
		initGui();
		adaugaButoane();
		initConnect();
	}
private:
	QDialog* dialog;
	QPushButton* btnWishRO = new QPushButton{ "RD" };

	QPushButton* btnGoleste = new QPushButton{ "Goleste" };
	QPushButton* btnRandom = new QPushButton{ "Random" };
	QPushButton* btnAddW = new QPushButton{ "AdaugaW" };

	QPushButton* btnExit = new QPushButton{ "&Exit" };
	QPushButton* btnAdd = new QPushButton{ "&Adauga" };
	QPushButton* btnDelet = new QPushButton{ "&Stergere" };
	QPushButton* btnMod = new QPushButton{ "&Modifica" };
	QPushButton* btnCauta = new QPushButton{ "&Cauta" };
	QPushButton* btnSuma = new QPushButton{ "&Suma" };
	QPushButton* btnSorFil = new QPushButton{ "&Sortare filtrare" };

	QPushButton* btnWishList = new QPushButton{ "&WishList" };

	QPushButton* btnUndo = new QPushButton{ "&Undo" };

	QLineEdit* txtDen = new QLineEdit;
	QLineEdit* txtDenMod = new QLineEdit;
	QLineEdit* txtDes = new QLineEdit;
	QLineEdit* txtTip = new QLineEdit;
	QLineEdit* txtPret = new QLineEdit;
	QLineEdit* txtSuma = new QLineEdit;

	QListWidget* lst = new QListWidget;

	QVBoxLayout* lybtn3 = new QVBoxLayout;
	QHBoxLayout* lybtn1_2 = new QHBoxLayout;
	QHBoxLayout* lyMain = new QHBoxLayout{};

	void initConnect();

	void loadData();

	void initGui();

	void adauga();

	void sterge(oferta oferta);

	void modifica(oferta oferta,string den);

	void cauta(string denumire);

	void suma();

	void see(oferta oferta);

	void clearAll();

	void undo();

	void adaugaButoane();

	void random();

	void adaugaW();

};