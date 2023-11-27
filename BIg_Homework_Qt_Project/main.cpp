#include <iostream>

#include "Game_Object.h"
int main(int argc, char* argv[])
{   
    using Game_Object_NS::Game_Object;
    Game_Object obj;
    Game_Object obj2;
    Game_Object_NS::objects;
    Game_Object::getElementById(1).id = 9;

    return 0;
}

/*
QApplication a(argc, argv);
MainWindow w;
w.setGeometry(0, 0, 600, 600);

*/