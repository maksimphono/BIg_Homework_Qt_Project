#include <iostream>

#include "Game_Object.h"

void handle0(Game_Object_NS::Game_Event* evnt) {
    *evnt->target->state = "asdfg";
}
void handle1(Game_Object_NS::Game_Event* evnt) {
    *evnt->object->state = "zxcvb";
}
#include "Item_Game_Object.h"

int main(int argc, char* argv[])
{   
    using Game_Object_NS::Game_Object;
    using Game_Object_NS::Game_Event;
    using Game_Object_NS::EventHandler;

    using Item_NS::Item;
    Item* item = new Item("Coal", "qw");
    Game_Object* obj = (Game_Object*)item;
    delete item;

    return 0;
}

/*
QApplication a(argc, argv);
MainWindow w;
w.setGeometry(0, 0, 600, 600);

*/