#include "wishGui.h"

void wishGui::initConnect() {
	(void)QObject::connect(btnExit, &QPushButton::clicked, [&]() {close(); });
	(void)QObject::connect(dial, &QDial::sliderMoved, [&]() {
		txtNumar->setText(QString::number(dial->value()));
		});
	(void)QObject::connect(btnRandom, &QPushButton::clicked, [&]() {random(txtNumar->text().toInt()); });
	(void)QObject::connect(btnGoleste, &QPushButton::clicked, [&]() {goleste(); });
	(void)QObject::connect(box, &QComboBox::currentTextChanged, [&]() {
		txtNumarOferta->setText(QString::number(box->currentIndex()));
		});
	(void)QObject::connect(btnAdauga, &QPushButton::clicked, [&]() {adauga(); });
	(void)QObject::connect(btnSterge, &QPushButton::clicked, [&]() {sterge(); });
	(void)QObject::connect(btnUndo, &QPushButton::clicked, [&]() {undo(); });
	(void)QObject::connect(lstWish, &QListWidget::clicked, [&]() {
		txtNumarOfertaSters->setText(QString::number(lstWish->currentRow())); });
}

void wishGui::loadData() {
	lstWish->clear();
	vector<oferta> l = ctr.getAllW();
	for (const auto& nume : l) {
		lstWish->addItem(QString::fromStdString(nume.getDenumire()));
	}
	txtElem->setText(QString::number(ctr.getAllW().size()));
}

void wishGui::loadDataLista() {
	box->clear();
	int i = 0;
	for (const auto nume : ctr.getAll()) {
		box->addItem(QString::number(i) + ") " + QString::fromStdString(nume.getDenumire()));
		i++;
	}
}


void wishGui::random(int nr) {
	try {
		ctr.randomServ(nr);
		loadData();
	}
	catch (ofertaWishException & ex) {
		stringstream ss;
		ss << ex;
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ss.str()));
	}
}

void wishGui::goleste() {
	ctr.goleste();
	loadData();
	txtElem->setText(QString::number(ctr.getAllW().size()));
}

void wishGui::adauga() {
	try {
		ctr.adaugaWish(txtNumarOferta->text().toInt());
		txtElem->setText(QString::number(ctr.getAllW().size()));
		loadData();
	}
	catch (ofertaWishException & ex) {
		stringstream ss;
		ss << ex;
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ss.str()));
	}
}

void wishGui::sterge() {
	try {
		ctr.stergeWish(txtNumarOfertaSters->text().toInt());
		txtElem->setText(QString::number(ctr.getAllW().size()));
		loadData();
	}
	catch (ofertaWishException & ex) {
		stringstream ss;
		ss << ex;
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ss.str()));
	}
}

void wishGui::undo() {
	try {
		ctr.undoWish();
		txtElem->setText(QString::number(ctr.getAllW().size()));
		loadData();
	}
	catch (ofertaWishException & ex) {
		stringstream ss;
		ss << ex;
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ss.str()));
	}
	catch (ofertaRepoException & ex) {
		stringstream ss;
		ss << ex;
		QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ss.str()));
	}
}

void wishListReadOnly::initGui() {
	ctr.addObserver(this);
	resize(600, 300);
	QVBoxLayout* lyMain = new QVBoxLayout;
	setLayout(lyMain);
}

void wishGui::initGui() {
	ctr.addObserver(this);
	QVBoxLayout* lyMain = new QVBoxLayout;

	QGridLayout* grid = new QGridLayout;

	QHBoxLayout* lyH1 = new QHBoxLayout;
	QHBoxLayout* lyH2 = new QHBoxLayout;
	QVBoxLayout* lyV1 = new QVBoxLayout;
	QVBoxLayout* lyV2 = new QVBoxLayout;

	QFormLayout* formly1 = new QFormLayout;
	QFormLayout* formly2 = new QFormLayout;

	dial->setNotchTarget(250);
	dial->setNotchesVisible(true);
	dial->setSingleStep(1);

	txtElem->setText(QString::number(ctr.getAllW().size()));

	setLayout(lyMain);

	formly1->addRow("Numar de elemente", txtElem);
	formly1->addRow("Numar de elemente de adaugat", txtNumar);
	txtNumar->setText("0");

	lyH1->addWidget(lstWish);
	lyV1->addLayout(formly1);
	lyV1->addWidget(dial);
	lyH1->addLayout(lyV1);

	lyMain->addLayout(lyH1);

	enum { NumGridRows = 3, NumBottons = 6 };

	grid->addWidget(btnRandom, 0, 0, 1, 1);
	grid->addWidget(btnGoleste, 0, 1, 1, 1);
	grid->addWidget(btnAdauga, 1, 0, 1, 1);
	grid->addWidget(btnSterge, 1, 1, 1, 1);
	grid->addWidget(btnUndo, 2, 0, 1, 1);
	grid->addWidget(btnExit, 2, 1, 1, 1);

	formly2->addRow("Numarul ofertei de sters", txtNumarOfertaSters);
	formly2->addRow("Numarul ofertei", txtNumarOferta);

	lyH2->addLayout(grid);
	lyV2->addLayout(formly2);
	lyV2->addWidget(box);
	lyH2->addLayout(lyV2);
	lyMain->addLayout(lyH2);
}