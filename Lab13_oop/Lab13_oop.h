#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lab13_oop.h"

class Lab13_oop : public QMainWindow
{
    Q_OBJECT

public:
    Lab13_oop(QWidget *parent = Q_NULLPTR);

private:
    Ui::Lab13_oopClass ui;
};
