#pragma once

#include "Game_Object.h"
/*
#include <vector>
#include <map>
*/
#include <string>
#include "Structure_Game_Object.h"

namespace Item_NS {
	using std::vector;
	using std::string;
	using std::map;
	using namespace Game_Object_NS;
	using Structure_NS::Orientation;

	typedef enum {FULL, LEFT, RIGHT} Cut_state;

	namespace Exceptions {
		using std::exception;
		typedef enum { T_id_already_exist, T_cant_cut, T_cant_create_more } Type;
		class Exception : public exception {
		private:
			Type type;
			string message;
		public:
			Exception(Type type, const string& message) : message(message), type(type) {}
			const char* what() const override {
				return message.c_str();
			}
			bool operator==(const Exception& other) {
				return this->type == other.type;
			}
		};

	}

	typedef struct {
		string resource;
		string id;
		int speed;
		bool cuttible;
		int price;
	} Raw_Item;
	
	class Item : Game_Object{
	private:
		int speed;
		bool cuttible;
		int price;
		string* resource;
		Cut_state cut_state;
	public:
		Item(Item& other) {
			this->speed = other.speed;
			this->cuttible = other.cuttible;
			this->price = other.price;
			this->resource = other.resource;
			this->cut_state = other.cut_state;
		}
		Item (string resource, string id = "", int speed = 0, bool cuttible = false, int price = 0)
			: speed(speed), cuttible(cuttible), price(price), cut_state(FULL), Game_Object(id.c_str()) {
			this->resource = new string(resource);
			*this->resource = resource;
			//Game_Object(id.c_str());
		}
		~Item() override {
			delete this->resource;
		}

		std::pair<Item*, Item*> cut() {
			if (!this->cuttible) return { NULL, NULL };
			Item* left_part = new Item(*this->resource, "", this->speed, false, this->price / 2);
			Item* right_part = new Item(*this->resource, "", this->speed, false, this->price / 2);
			left_part->cut_state = LEFT;
			right_part->cut_state = RIGHT;

			delete this;
			return { left_part , right_part };
		}

		void move(Orientation) {
			// TODO : implement movement system
			return;
		}

		stringstream* repr(std::ofstream& stream) const override {
			stringstream* report = new stringstream();
			*report << "\tItem object id = " << this->getId() << ", " << this << ";\n" <<
				"\t\tSpeed = " << this->speed << ";\n" <<
				"\t\tPrice = " << this->price << ";\n" <<
				"\t\tCarried resource = " << *this->resource << ";\n" <<
				"\t\tIs cuttable = " << this->cuttible << ";\n";
			if (!this->cuttible && this->cut_state != FULL) {
				if (this->cut_state == LEFT)
					*report << "\t\tLeft half;";
				else 
					*report << "\t\tRight half;";
			}
			*report << "\n\n";

			stream << report->str();
			return report;
		}

	public: // getters:
		int getSpeed() const {
			return this->speed;
		}
		int getPrice() const {
			return this->price;
		}
		int getCuttible() const {
			return this->cuttible;
		}
		string getResource() const {
			return *this->resource;
		}
		Cut_state getCutState() {
			return this->cut_state;
		}
	public: // setters:
		void setSpeed(int speed) {
			this->speed = speed;
		}
		void setPrice(int price) {
			this->price = price;
		}
		void setCuttible(bool v) {
			this->cuttible = v;
		}
		string setResource(string& newResource) {
			*this->resource = newResource;
		}
	};
}