#pragma once
#include "Structure_Game_Object.h"
#include "Item_Game_Object.h"

namespace Mine_NS {
	using std::vector;
	using std::string;
	using std::map;
	using std::stringstream;
	using Structure_NS::Structure;
	using Structure_NS::Orientation;
	using Item_NS::Raw_Item;

	class Mine : Structure {
	private:
		int frequency;
		Raw_Item* item_sample;
		
	public:
		Mine(int frequency, string resource, string id = "")
			: frequency(frequency), item_sample(new Raw_Item({resource, "", 1, false, 0})), Structure(id) {}

		Mine(int frequency, Raw_Item* sample, string id = "")
			: frequency(frequency), item_sample(sample), Structure(id) {}

		~Mine() override {
			delete this->item_sample;
		}
		
		void emit() const {
			if (this->isEnabled()) {
				// TODO: realize items emitting system
				return;
			}
		}

		void tick(ull globalTick) const override {
			if (globalTick % this->frequency == 0) {
				//this->setState("emit");
				this->emit();
			}
		}

		stringstream* repr(std::ofstream& stream) const override {
			stringstream* report = new stringstream();
			*report << "\tMine object id = " << this->getId() << ", " << this << ";\n" <<
				"\t\tFrequency = " << this->frequency << ";\n" <<
				"\t\tProduced resource = " << this->item_sample->resource << ";\n" <<
				"\t\tResource speed = " << this->item_sample->speed << ";\n" <<
				"\t\tResource price = " << this->item_sample->price << ";\n" <<
				"\t\tResource cuttable = " << this->item_sample->cuttible << ";";
			*report << "\n\n";

			stream << report->str();
			return report;
		}

	public: // getters:
		int getFriquency() const {
			return this->frequency;
		}
		Raw_Item* getItem() const {
			return this->item_sample;
		}
	public: // setters:
		void setFriquency(int newFrequency){
			this->frequency = newFrequency;
		}
		void setItem(Raw_Item& newSample){
			this->item_sample = &newSample;
		}
		void setItem(string resource) {
			this->item_sample = new Raw_Item({ resource, "", 0, 0, 0 });
		}
	};
}