#include "consolGui.h"
#include "sorGui.h"
#include "wishGui.h"

void consolGui::initConnect() {

	(void)QObject::connect(btnExit, &QPushButton::clicked, [&]() {close(); });
	(void)QObject::connect(btnAdd, &QPushButton::clicked, [&]() {adauga(); });
	(void)QObject::connect(btnSuma, &QPushButton::clicked, [&]() {suma(); });
	(void)QObject::connect(btnUndo, &QPushButton::clicked, [&]() {undo(); });
	(void)QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {
		auto sel = lst->selectedItems();
		if (sel.isEmpty()) {
			clearAll();
		}
		else {
			auto selItem = sel.at(0);
			string den = selItem->text().toStdString();
			oferta o = ctr.cautare(den);
			see(o);
		}
		});
	(void)QObject::connect(btnDelet, &QPushButton::clicked, [&]() {
		oferta o{ txtDen->text().toStdString(),txtDes->text().toStdString(), txtTip->text().toStdString(), txtPret->text().toDouble() };
		sterge(o); });

	(void)QObject::connect(btnMod, &QPushButton::clicked, [&]() {
		oferta o{ txtDen->text().toStdString(),txtDes->text().toStdString(), txtTip->text().toStdString(), txtPret->text().toDouble() };
		string den = txtDenMod->text().toStdString();
		modifica(o, den); });

	(void)QObject::connect(btnCauta, &QPushButton::clicked, [&]() {
		string den = txtDen->text().toStdString();
		cauta(den);
		});
	(void)QObject::connect(btnSorFil, &QPushButton::clicked, [&]() {
		auto gui=new sorGui{ ctr };
		gui->show();
		});
	(void)QObject::connect(btnWishList, &QPushButton::clicked, [&]() {
		auto gui = new wishGui{ ctr };
		gui->show();
		});
	(void)QObject::connect(btnWishRO, &QPushButton::clicked, [&]() {
		auto gui = new wishListReadOnly{ ctr };
		gui->show();
		});
	(void)QObject::connect(btnRandom, &QPushButton::clicked, [&]() {random();});
	(void)QObject::connect(btnGoleste, &QPushButton::clicked, [&]() {ctr.goleste(); });
	(void)QObject::connect(btnAddW, &QPushButton::clicked, [&]() {adaugaW(); });
}

void consolGui::loadData() {
	lst->clear();
	vector<oferta> l = ctr.getAll();
	for (const auto& nume : l) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(nume.getDenumire()));
		if (nume.getPret() > 1000)
			item->setBackground(QBrush{ Qt::red,Qt::SolidPattern });
		lst->addItem(item);
	}
	adaugaButoane();
}

void consolGui::adaugaButoane() {
	while (auto button = lybtn3->takeAt(0))
	{
		delete button->widget();
		delete button;
	}
	for (const auto& i : ctr.getAll()) {
		auto btn = new QPushButton{ QString::fromStdString(i.getDenumire()) };
		lybtn3->addWidget(btn);
		(void)QObject::connect(btn, &QPushButton::clicked, [this,btn,i]() {
			ctr.stergere(i.getDenumire());
			loadData();
			adaugaButoane();
			});
	}
}

void consolGui::adauga() {
	auto pret = txtPret->text().toDouble();
	if (pret > 0) {
		try {
			ctr.addOferta(txtDen->text().toStdString(), txtDes->text().toStdString(), txtTip->text().toStdString(), pret);
			loadData();
			adaugaButoane();
		}
		catch (ofertaRepoException & ex) {
			stringstream ss;
			ss << ex;
			QMessageBox::warning(this, "Warning", QString::fromStdString(ss.str()));
		}
		catch (ValidateException & ex) {
			stringstream ss;
			ss << ex;
			QMessageBox::warning(this, "Warning", QString::fromStdString(ss.str()));
		}
	}
	else {
		QMessageBox::warning(this, "Warning", "Pretul trebui sa fie un numar mai mare decat 0");
	}
}

void consolGui::random() {
	dialog = new QDialog{ btnRandom };
	QHBoxLayout* ly = new QHBoxLayout{ dialog };
	QLabel* lb = new QLabel{ "Introduceti numarul pentru random!" };
	QLineEdit* edit = new QLineEdit;
	QPushButton* bEx = new QPushButton{ "Gata" };
	ly->addWidget(lb);
	ly->addWidget(edit);
	ly->addWidget(bEx);
	dialog->setLayout(ly);
	dialog->show();

	(void)QObject::connect(bEx, &QPushButton::clicked, [&,edit]() {
		ctr.randomServ(edit->text().toInt());
		delete dialog;
		});
}

void consolGui::adaugaW() {
	dialog = new QDialog{ btnAddW };
	QHBoxLayout* ly = new QHBoxLayout{ dialog };
	QLabel* lb = new QLabel{ "Introduceti numarul pentru adauga!" };
	QLineEdit* edit = new QLineEdit;
	QPushButton* bEx = new QPushButton{ "Gata" };
	ly->addWidget(lb);
	ly->addWidget(edit);
	ly->addWidget(bEx);
	dialog->setLayout(ly);
	dialog->show();
	(void)QObject::connect(bEx, &QPushButton::clicked, [&, edit]() {
		try {
			ctr.adaugaWish(edit->text().toInt());
			delete dialog;
		}
		catch (ofertaWishException & ex) {
			stringstream ss;
			ss << ex;
			QMessageBox::warning(this, "Warning", QString::fromStdString(ss.str()));
		}
		});
}


void consolGui::sterge(oferta oferta) {
	try {
		ctr.stergere(oferta.getDenumire());
		loadData();
		adaugaButoane();
	}
	catch (ofertaRepoException & ex) {
		stringstream ss;
		ss << ex;
		QMessageBox::warning(this, "Warning", QString::fromStdString(ss.str()));
	}
	clearAll();
}

void consolGui::modifica(oferta oferta,string den) {
	auto pret = txtPret->text().toDouble();
	if (pret > 0) {
		try {
			ctr.modOferta(den, txtDen->text().toStdString(), txtDes->text().toStdString(), txtTip->text().toStdString(), pret);
			loadData();
			adaugaButoane();
		}
		catch (ofertaRepoException & ex) {
			stringstream ss;
			ss << ex;
			QMessageBox::warning(this, "Warning", QString::fromStdString(ss.str()));
		}
		catch (ValidateException & ex) {
			stringstream ss;
			ss << ex;
			QMessageBox::warning(this, "Warning", QString::fromStdString(ss.str()));
		}
	}
	txtDenMod->setText("");
	clearAll();
}

void consolGui::cauta(string den) {
	try {
		see(ctr.cautare(den));
	}
	catch (ofertaRepoException & ex) {
		stringstream ss;
		ss << ex;
		QMessageBox::warning(this, "Warning", QString::fromStdString(ss.str()));
	}
}

void consolGui::suma() {
	txtSuma->setText("");
	txtSuma->setText(QString::number(ctr.suma()));
}

void consolGui::clearAll() {
	txtDen->setText("");
	txtDes->setText("");
	txtTip->setText("");
	txtPret->setText("");
}

void consolGui::see(oferta oferta) {
	txtDen->setText(QString::fromStdString(oferta.getDenumire()));
	txtDes->setText(QString::fromStdString(oferta.getDestinatie()));
	txtTip->setText(QString::fromStdString(oferta.getTip()));
	txtPret->setText(QString::number(oferta.getPret()));
}

void consolGui::undo() {
	try {
		ctr.undo();
		loadData();
	}
	catch (ofertaRepoException & ex) {
		stringstream ss;
		ss << ex;
		QMessageBox::warning(this, "Warning", QString::fromStdString(ss.str()));
	}
}
void consolGui::initGui() {

	QVBoxLayout* lyV1 = new QVBoxLayout{};
	QVBoxLayout* lyV2 = new QVBoxLayout{};

	QHBoxLayout* lyH1 = new QHBoxLayout{};

	QHBoxLayout* lybtn1 = new QHBoxLayout;
	QVBoxLayout* lybtn2 = new QVBoxLayout;
	QHBoxLayout* lybtn4 = new QHBoxLayout;

	QFormLayout* formly1 = new QFormLayout;

	setLayout(lyMain);

	lyV1->addWidget(lst);


	lybtn1->addWidget(btnUndo);
	lybtn1->addWidget(btnExit);
	lybtn1->addWidget(btnWishRO);

	lybtn2->addWidget(btnAdd);
	lybtn2->addWidget(btnDelet);
	lybtn2->addWidget(btnMod);
	lybtn2->addWidget(btnCauta);
	lybtn2->addWidget(btnSuma);

	lyV1->addLayout(lybtn1);
	lybtn1_2->addWidget(btnWishList);
	lybtn1_2->addWidget(btnSorFil);
	lybtn4->addWidget(btnRandom);
	lybtn4->addWidget(btnGoleste);
	lybtn4->addWidget(btnAddW);
	lyV1->addLayout(lybtn1_2);
	lyV1->addLayout(lybtn4);

	lyMain->addLayout(lyV1);

	formly1->addRow("Denumire de modificat", txtDenMod);
	formly1->addRow("Denumire", txtDen);
	formly1->addRow("Destinatie", txtDes);
	formly1->addRow("Tip", txtTip);
	formly1->addRow("Pret", txtPret);
	formly1->addRow("Suma", txtSuma);


	lyV2->addLayout(formly1);
	lyV2->addLayout(lybtn2);

	lyMain->addLayout(lyV2);

	lyMain->addLayout(lybtn3);
}