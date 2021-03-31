#include <stdlib.h>
#include <crtdbg.h>
#include <QtWidgets/QApplication>
#include "consolGui.h"
#include "console.h"
#include "service.h"
#include "repository.h"
#include "wishlist.h"
#include "validator.h"

void testAll() {
	testeRepo();
	testService();
	testValidator();
	testWish();
}

int main(int argc, char* argv[]) {
	testAll();
	{
		QApplication a(argc, argv);
		//repository rep;
		//repoNou rep{ 0.50 };
		repositoryFile rep{ "repo.txt" };
		ofertaValidator val;
		repositoryW wish;
		service ctr{ rep,val,wish };
		//ConsolUI ui{ ctr };
		//ui.start();
		consolGui gui{ ctr };
		gui.show();
		return a.exec();
	}
}

