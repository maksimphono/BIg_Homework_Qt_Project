#include <iostream>

#include "Game_Object.h"

void handle0(Game_Object_NS::Game_Event* evnt) {
    std::cout << 0;
}
void handle1(Game_Object_NS::Game_Event* evnt) {
    std::cout << 1;
}

int main(int argc, char* argv[])
{   
    using Game_Object_NS::Game_Object;
    using Game_Object_NS::EventHandler;
    Game_Object obj("qw");
    Game_Object obj2;

    obj.bind(T1, (EventHandler)handle0);
    obj.bind(T1, (EventHandler)handle1);
    obj.fireSeries(T1, NULL);
    obj.unbind(T1, 1);

    return 0;
}

/*
QApplication a(argc, argv);
MainWindow w;
w.setGeometry(0, 0, 600, 600);

*/