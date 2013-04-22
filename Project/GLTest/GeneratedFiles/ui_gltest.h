/********************************************************************************
** Form generated from reading UI file 'gltest.ui'
**
** Created: Tue Mar 12 11:12:13 2013
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GLTEST_H
#define UI_GLTEST_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GLTestClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GLTestClass)
    {
        if (GLTestClass->objectName().isEmpty())
            GLTestClass->setObjectName(QString::fromUtf8("GLTestClass"));
        GLTestClass->resize(600, 400);
        menuBar = new QMenuBar(GLTestClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        GLTestClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GLTestClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        GLTestClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(GLTestClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        GLTestClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(GLTestClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        GLTestClass->setStatusBar(statusBar);

        retranslateUi(GLTestClass);

        QMetaObject::connectSlotsByName(GLTestClass);
    } // setupUi

    void retranslateUi(QMainWindow *GLTestClass)
    {
        GLTestClass->setWindowTitle(QApplication::translate("GLTestClass", "GLTest", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GLTestClass: public Ui_GLTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GLTEST_H
