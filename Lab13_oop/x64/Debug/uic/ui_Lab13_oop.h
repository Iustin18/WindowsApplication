/********************************************************************************
** Form generated from reading UI file 'Lab13_oop.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAB13_OOP_H
#define UI_LAB13_OOP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Lab13_oopClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Lab13_oopClass)
    {
        if (Lab13_oopClass->objectName().isEmpty())
            Lab13_oopClass->setObjectName(QString::fromUtf8("Lab13_oopClass"));
        Lab13_oopClass->resize(600, 400);
        menuBar = new QMenuBar(Lab13_oopClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        Lab13_oopClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Lab13_oopClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Lab13_oopClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(Lab13_oopClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Lab13_oopClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Lab13_oopClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Lab13_oopClass->setStatusBar(statusBar);

        retranslateUi(Lab13_oopClass);

        QMetaObject::connectSlotsByName(Lab13_oopClass);
    } // setupUi

    void retranslateUi(QMainWindow *Lab13_oopClass)
    {
        Lab13_oopClass->setWindowTitle(QCoreApplication::translate("Lab13_oopClass", "Lab13_oop", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Lab13_oopClass: public Ui_Lab13_oopClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAB13_OOP_H
