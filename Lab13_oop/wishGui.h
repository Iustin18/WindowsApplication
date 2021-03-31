#pragma once
#include "service.h"
#include "Observator.h"
#include <qpainter.h>
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <Qtwidgets/qboxlayout.h>
#include <Qtwidgets/qlineedit.h>
#include <Qtwidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <qdebug.h>
#include <qcombobox.h>
#include <qmessagebox.h>
#include <vector>
#include <sstream>
#include <qdial.h>

class wishGui : public QWidget, public Observer {
public:
	service& ctr;

	wishGui(service& ctr) noexcept :ctr{ ctr } {
		initGui();
		loadData();
		loadDataLista();
		initConnect();
	}
	~wishGui() {
		ctr.removeObserver(this);
	}
private:
	QPushButton* btnExit = new QPushButton{ "&Exit" };
	QPushButton* btnAdauga = new QPushButton{ "&Adauga" };
	QPushButton* btnSterge = new QPushButton{ "&Sterge" };
	QPushButton* btnGoleste = new QPushButton{ "&Goleste" };
	QPushButton* btnUndo = new QPushButton{ "&Undo" };
	QPushButton* btnRandom = new QPushButton{ "&Random" };

	QListWidget* lstWish = new QListWidget;
	QComboBox* box = new QComboBox;

	QLineEdit* txtElem = new QLineEdit;
	QLineEdit* txtNumar = new QLineEdit;
	QLineEdit* txtNumarOferta = new QLineEdit;
	QLineEdit* txtNumarOfertaSters = new QLineEdit;

	QDial* dial = new QDial;

	void update() override {
		loadData();
	}

	void initGui();
	void loadData();
	void loadDataLista();
	void initConnect();

	void random(int nr);

	void goleste();

	void adauga();

	void sterge();

	void undo();


};

class wishListReadOnly : public QWidget,public Observer {
private:
	service& ctr;
	void initGui();
public:
	wishListReadOnly(service& ctr) noexcept :ctr{ ctr } {
		initGui();
		loadData();
	}
	~wishListReadOnly() {
		ctr.removeObserver(this);
	}

	void update() override {
		loadData();
	}

	void loadData() {
		repaint();
	}

	void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };
		QPen pen;
		pen.setStyle(Qt::SolidLine);
		pen.setColor(Qt::red);
		pen.setWidth(4);
		p.setPen(pen);
		for (auto i : ctr.getAllW()) {
			QRect forma(qrand() % 350, qrand() % 150, qrand() % 250, qrand() % 150);
			forma.normalized();
			p.drawRect(forma);
		}
	}
};