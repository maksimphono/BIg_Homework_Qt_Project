#pragma once

#include "Structure_Game_Object.h"
#include "Game_State.h"
#include "Item_Game_Object.h"
#include <map>

namespace Factory_NS {
	using Structure_NS::Structure;
	using namespace Game_State_NS;
	using std::map;
	using Item_NS::Item;


	class Factory : public Structure {
	private:
		map<string, double>* price_table;
	public:
		Factory(string id = "") : price_table(new map<string, double>()), Structure(id) {}
		~Factory() {
			delete this->price_table;
		}
		
		void receiveItem(Item* item) {
			if (item == NULL) return;
			if (this->price_table->find(item->getResource()) != this->price_table->end()) {
				mainGameState.balance += (*this->price_table)[item->getResource()];
			}
			else {
				mainGameState.balance += item->getPrice();
			}
			if (item->getCutState() != Item_NS::FULL)
				mainGameState.sold_items[item->getResource()] += .5;
			else
				mainGameState.sold_items[item->getResource()] += 1;
		}
	};
}