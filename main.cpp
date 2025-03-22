#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "mainWindow.h"

using namespace std;

int main(int argc, char** argv){

	QApplication app(argc, argv);

	MainWindow* mw = new MainWindow();
	mw->show();

	return app.exec();

}
