

#include "stdafx.h"
#include "gltest.h"
#include <QtGui/QApplication>



int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GLTest w;
	w.show();
	return a.exec();
}
