#include <iostream>

#include "Game_Object.h"

void handle(Game_Object_NS::Game_Event* evnt) {
    std::cout << 0;
}

int main(int argc, char* argv[])
{   
    using Game_Object_NS::Game_Object;
    using Game_Object_NS::EventHandler;
    Game_Object obj("qw");
    Game_Object obj2;
    
    obj.bind(T1, (EventHandler)handle);
    obj.fireSeries(T1, NULL);

    return 0;
}

/*
QApplication a(argc, argv);
MainWindow w;
w.setGeometry(0, 0, 600, 600);

*/