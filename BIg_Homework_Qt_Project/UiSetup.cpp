#include "MainWindow.h"
#include <QtWidgets/QApplication>

int uiSetup(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
