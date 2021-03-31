#include "sorGui.h"

void sorGui::initConnect() {
	(void)QObject::connect(btnExit, &QPushButton::clicked, [&]() {close(); });
	(void)QObject::connect(btnRaport, &QPushButton::clicked, [&]() {raport(); });
	(void)QObject::connect(btnSorDen, &QPushButton::clicked, [&]() {sorDen(); });
	(void)QObject::connect(btnSorDes, &QPushButton::clicked, [&]() {sorDes(); });
	(void)QObject::connect(btnSorTipPret, &QPushButton::clicked, [&]() {sorTipPret(); });
	(void)QObject::connect(btnSorPret, &QPushButton::clicked, [&]() {sorPret(); });
	(void)QObject::connect(btnFilPret, &QPushButton::clicked, [&]() {filPret(); });
	(void)QObject::connect(btnFilPretM, &QPushButton::clicked, [&]() {filPretMinMax(); });
	(void)QObject::connect(btnFilDes, &QPushButton::clicked, [&]() {filDes(); });
}

void sorGui::loadFS(vector<oferta> l) {
	lstFS->clear();
	for (auto i : l) {
		lstFS->addItem(QString::fromStdString(i.getDenumire()));
	}
	adaugaButoane(l);
}

void sorGui::adaugaButoane(vector<oferta> l) {
	while (auto button = lybtn3->takeAt(0))
	{
		delete button->widget();
		delete button;
	}
	for (const auto& i : l) {
		auto btn = new QPushButton{ QString::fromStdString(i.getDenumire()) };
		lybtn3->addWidget(btn);
	}
}

void sorGui::raport() {
	vector<DTO> l;
	ctr.raport(l);
	lstFS->clear();
	for (auto i : l) {
		lstFS->addItem(QString::fromStdString(i.denumire) + " " + QString::number(i.count));
	}
}

void sorGui::sorDen() {
	loadFS(ctr.sortByDenumire());
}

void sorGui::sorDes() {
	loadFS(ctr.sortByDestinatie());
}

void sorGui::sorTipPret() {
	loadFS(ctr.sortByTipPret());
}

void sorGui::sorPret() {
	loadFS(ctr.sortByPret());
}

void sorGui::filPret() {
	loadFS(ctr.filtrarePretMaiMic(txtPretMin->text().toDouble()));
}

void sorGui::filPretMinMax() {
	loadFS(ctr.filtrarePret(txtPretMin->text().toDouble(), txtPretMax->text().toDouble()));
}

void sorGui::filDes() {
	loadFS(ctr.filtrareDestinatie(txtDestinatie->text().toStdString()));
}

void sorGui::initGui() {
	QHBoxLayout* lyMain = new QHBoxLayout{};

	QHBoxLayout* lyH1 = new QHBoxLayout{};
	QVBoxLayout* lyV1 = new QVBoxLayout{};

	QGridLayout* grid = new QGridLayout;

	QFormLayout* formly2 = new QFormLayout;

	enum{NumGridRows=5, NumButtons=9};

	setLayout(lyMain);

	grid->addWidget(btnSorDen,0,0,1,1);
	grid->addWidget(btnSorDes,1,0,1,1);
	grid->addWidget(btnSorTipPret,2,0,1,1);
	grid->addWidget(btnSorPret,3,0,1,1);

	lyH1->addWidget(lstFS);


	formly2->addRow("Pret/Pret min", txtPretMin);
	formly2->addRow("Pret max", txtPretMax);
	formly2->addRow("Destinatie", txtDestinatie);

	grid->addWidget(btnRaport,0,1,1,1);
	grid->addWidget(btnFilPret,1,1,1,1);
	grid->addWidget(btnFilPretM,2,1,1,1);
	grid->addWidget(btnFilDes,3,1,1,1);
	grid->addWidget(btnExit, 4, 0, 1, 1);

	lyH1->addLayout(formly2);
	lyV1->addLayout(lyH1);
	lyV1->addLayout(grid);

	lyMain->addLayout(lyV1);
	lyMain->addLayout(lybtn3);
}