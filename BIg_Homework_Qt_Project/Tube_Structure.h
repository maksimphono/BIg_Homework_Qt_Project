#pragma once

#include "Mine_Structure.h"


namespace Tube_NS {
	using std::vector;
	using std::string;
	using std::map;
	using Structure_NS::Structure;
	using Structure_NS::Orientation;
	using Item_NS::Item;

	const int STEPS_TO_PASS = 60;

	class TubeBlock : Structure {
	
	private:
		union {
			TubeBlock* next;
		};
		union {
			TubeBlock* prev;
		};
		Item* floating_item;
		int steps_passed;

	public:
		TubeBlock(TubeBlock& another) 
			: next(another.next), prev(another.prev), steps_passed(another.steps_passed), Structure(another.orientation, "") {}
		TubeBlock(TubeBlock* prev = NULL, TubeBlock* next = NULL, Orientation orientation = Orientation::NONE, string id = "") 
			: next(next), prev(prev), steps_passed(0), Structure(orientation, id) {}
		~TubeBlock() override{
			delete floating_item;
			this->prev->next = NULL;
		}

		void tick(ull globalTick) override {
			if (globalTick % floating_item->getSpeed() == 0) {
				if (steps_passed == STEPS_TO_PASS / 2 && this->next && this->next->floating_item == NULL) {
					this->next->floating_item = this->floating_item;
					this->floating_item = NULL;
					steps_passed = 0;
				}
				else if (steps_passed > STEPS_TO_PASS / 2) {
					floating_item->move(this->orientation);
				}
				else {
					floating_item->move(this->prev->orientation);
				}
				steps_passed++;
			}
		}
		void attach(TubeBlock* block) {
			this->next = block;
		}
	public: // getters:

	};

}