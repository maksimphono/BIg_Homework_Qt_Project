#include <iostream>

#include "Game_Object.h"

void handle0(Game_Object_NS::Game_Event* evnt) {
    *evnt->target->state = "asdfg";
}
void handle1(Game_Object_NS::Game_Event* evnt) {
    *evnt->object->state = "zxcvb";
}

int main(int argc, char* argv[])
{   
    using Game_Object_NS::Game_Object;
    using Game_Object_NS::Game_Event;
    using Game_Object_NS::EventHandler;
    Game_Object* obj = new Game_Object("qw");
    Game_Object obj2;
    Game_Event* ev = new Game_Event(T1, obj, &obj2);

    //obj->bind(T1, (EventHandler)handle0);
    //obj->bind(T1, (EventHandler)handle1);
    obj->fireSeries(T1, ev);
    obj->fire(T1, handle0, ev);
    delete obj;
    delete ev;

    return 0;
}

/*
QApplication a(argc, argv);
MainWindow w;
w.setGeometry(0, 0, 600, 600);

*/