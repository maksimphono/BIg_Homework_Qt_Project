#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainWIndow.h"

class MainWindow : public QMainWindow
{
    //Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::mainWIndowClass ui;
};
