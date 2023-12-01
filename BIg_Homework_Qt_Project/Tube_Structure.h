#pragma once

#include "Mine_Structure.h"


namespace Tube_NS {
	using std::vector;
	using std::string;
	using std::map;
	using std::stringstream;
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
			: next(next), prev(prev), steps_passed(0), Structure(orientation, id) {
			if (this->prev) {
				prev->next = this;
			}
		}
		~TubeBlock() override {
			delete floating_item;
			this->prev->next = NULL;
		}

		void tick(ull globalTick) const override {
			if (globalTick % floating_item->getSpeed() == 0) {
				if (steps_passed == STEPS_TO_PASS / 2 && this->next && this->next->floating_item == NULL) {
					// TODO: realize how and when one block should pass item to the next
					this->next->floating_item = this->floating_item;
				}
				else if (steps_passed > STEPS_TO_PASS / 2) {
					floating_item->move(this->orientation);
				}
				else {
					floating_item->move(this->prev->orientation);
				}
			}
		}
		TubeBlock* attach(TubeBlock* block) {
			if ((this->orientation == Orientation::UP && block->orientation != Orientation::DOWN) ||
				(block->orientation == Orientation::UP && this->orientation != Orientation::DOWN) ||
				(this->orientation == Orientation::LEFT && block->orientation != Orientation::RIGHT) ||
				(block->orientation == Orientation::LEFT && this->orientation != Orientation::RIGHT))
			{
				this->next = block;
				block->prev = this;
				return this->next;
			}
			return this;
		}

		stringstream* repr(std::ofstream& stream) const override {
			stringstream* report = new stringstream();
			*report << "\Tube object id = " << this->getId() << ", " << this << ";\n";
			*report << "\n\n";

			stream << report->str();
			return report;
		}

	public: // getters:

	};

}