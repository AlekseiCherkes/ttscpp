#include "admin.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Admin w;
	w.show();
	return a.exec();
}
