#pragma once
#include "Structure_Game_Object.h"
#include "Item_Game_Object.h"

namespace Mine_NS {
	using std::vector;
	using std::string;
	using std::map;
	using Structure_NS::Structure;
	using Structure_NS::Orientation;
	using Item_NS::Item;

	class Mine : Structure {
	private:
		int frequency;
		Item* item_sample;
		
	public:
		Mine(int frequency, string resource, string id = "")
			: frequency(frequency), item_sample(new Item(resource, "", 1)), Structure(id) {}

		Mine(int frequency, Item* sample, string id = "")
			: frequency(frequency), item_sample(sample), Structure(id) {}

		~Mine() override {
			delete this->item_sample;
		}
		
		void emit() {
			if (this->isEnabled()) {
				// TODO: realize items emitting system
				return;
			}
		}

		void tick(ull globalTick) override {
			if (globalTick % this->frequency == 0) {
				__super::setState("emit");
				this->emit();
			}
			else {
				__super::setState("reloading");
			}
		}

	public: // getters:
		int getFriquency() const {
			return this->frequency;
		}
		Item* getItem() const {
			return this->item_sample;
		}
	public: // setters:
		void setFriquency(int newFrequency){
			this->frequency = newFrequency;
		}
		void setItem(Item& newSample){
			this->item_sample = &newSample;
		}
		void setItem(string resource) {
			this->item_sample = new Item(resource);
		}
	};
}