#pragma once
#include <map>
#include <string>
#include <sstream>
#include <fstream>

namespace Game_State_NS {
	using std::map;
	using std::string;
	using std::ofstream;
	using std::stringstream;

	class GameState {
	private:
		int balance;
		map<string, int> sold_items;
	public:
		GameState() :balance(0) {}
		~GameState() {}

		stringstream* repr(std::ofstream& stream) const {
			stringstream* report = new stringstream();
			*report << "\tGame State:" << "\n" <<
				"\t\tCurrent balance: " << this->balance << "\n"
				"\t\tSold Items:" << "\n";
			for (const auto& item : this->sold_items) {
				*report << "\t\t\t" << item.first << " : " << item.second << ";\n";
			}
			*report << "\n\n";

			stream << report->str();
			return report;
		}
	};
}