#include <iostream>
#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QTimer>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setGeometry(0, 0, 600, 600);

    QGraphicsScene scene;
    QGraphicsView view(&scene);

    QPixmap pixmap("D:/img.png");
    QGraphicsPixmapItem* item = scene.addPixmap(pixmap);

    item->setPos(0, 0);

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        item->setPos(item->x() + 1, item->y() + 1);
    }
    );
    timer.start(5);
    view.show();
    return a.exec();
}