#ifndef GLTEST_H
#define GLTEST_H

#include <QtGui/QMainWindow>
#include "ui_gltest.h"

class GLTest : public QMainWindow
{
	Q_OBJECT

public:
	GLTest(QWidget *parent = 0, Qt::WFlags flags = 0);
	~GLTest();

private:
	Ui::GLTestClass ui;
};

#endif // GLTEST_H
