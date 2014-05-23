#include "drc.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	drc w;
	w.show();
	return a.exec();
}
