#include <iostream>
#include "consts.h"

#include "Game_State.h"
#include "Item_Game_Object.h"
#include "Mine_Structure.h"
#include "Tube_Structure.h"

void handle0(Game_Object_NS::Game_Event* evnt) {
    *evnt->target->state = "asdfg";
}
void handle1(Game_Object_NS::Game_Event* evnt) {
    *evnt->object->state = "zxcvb";
}
class Logger {
public:
    const wchar_t* filepath = L"D:/Maksim/学习/2023秋/高级程序/Big hw/log.txt";
    std::ofstream* file;

    Logger() {
        this->file = new std::ofstream(filepath);
    }
    ~Logger() {
        if (this->file->is_open())
            this->file->close();
        delete this->file;
    }
    void reprAll() {
        for (const auto& obj : Game_Object_NS::objects_list) {
            if (obj)
                obj->repr(*this->file);
        }
    }
};
void repr() {
    Logger* logger = new Logger();
    logger->reprAll();
    delete logger;
}

int main(int argc, char* argv[])
{   
    using Game_Object_NS::Game_Object;
    using Game_Object_NS::Game_Event;
    using Game_Object_NS::EventHandler;
    using Mine_NS::Mine;
    using Item_NS::Item;
    using Tube_NS::TubeBlock;
    using Structure_NS::Orientation;
    Mine* mine = new Mine(3, "Coal", "qw");
    Item* item = new Item("Coal", "", 1, true, 4);
    std::pair<Item*, Item*> p = item->cut();
    repr();

    TubeBlock* t1 = new TubeBlock(NULL, NULL, Orientation::LEFT, "1");
    TubeBlock* t2 = new TubeBlock(NULL, NULL, Orientation::LEFT, "2");
    TubeBlock* t3 = new TubeBlock(NULL, NULL, Orientation::DOWN, "3");
    TubeBlock* t4 = new TubeBlock(NULL, NULL, Orientation::UP, "4");

    t1
        ->attach(t2)
        ->attach(t3)
        ->attach(t4);

    for (int i = 0; i < 9; i++) {
        t1->tick(i);
        t2->tick(i);
        t3->tick(i);
    }

    delete t1;

    return 0;
}

/*
QApplication a(argc, argv);
MainWindow w;
w.setGeometry(0, 0, 600, 600);

*/