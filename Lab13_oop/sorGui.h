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

class sorGui : public QWidget {
public:
	service& ctr;

	sorGui(service& ctr) noexcept :ctr{ ctr } {
		initGui();
		initConnect();
		adaugaButoane(ctr.getAll());
	}
private:
	QPushButton* btnExit = new QPushButton{ "&Exit" };
	QPushButton* btnRaport = new QPushButton{ "&Raport" };

	QPushButton* btnSorDen = new QPushButton{ "&Sortare Denumire" };
	QPushButton* btnSorDes = new QPushButton{ "&Sortare Destinatie" };
	QPushButton* btnSorTipPret = new QPushButton{ "&Sortare Tip si Pret" };
	QPushButton* btnSorPret = new QPushButton{ "&Sortare Pret" };

	QPushButton* btnFilPret = new QPushButton{ "&Filtrare Pret" };
	QPushButton* btnFilPretM = new QPushButton{ "&Filtrare Pret minim, maxim" };
	QPushButton* btnFilDes = new QPushButton{ "&Filtrare Destinatie" };

	QLineEdit* txtPretMin = new QLineEdit;
	QLineEdit* txtPretMax = new QLineEdit;
	QLineEdit* txtDestinatie = new QLineEdit;

	QVBoxLayout* lybtn3 = new QVBoxLayout;

	QListWidget* lstFS = new QListWidget;

	void initGui();

	void initConnect();

	void loadFS(vector<oferta> l);

	void raport();

	void sorDen();

	void sorDes();

	void sorTipPret();

	void sorPret();

	void filPret();

	void filPretMinMax();

	void filDes();

	void adaugaButoane(vector<oferta> l);
};