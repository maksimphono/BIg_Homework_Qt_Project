#pragma once

#include "Game_Object.h"
/*
#include <vector>
#include <map>
*/
#include <string>

namespace Item_NS {
	using std::vector;
	using std::string;
	using std::map;
	using namespace Game_Object_NS;

	namespace Exceptions {
		using std::exception;
		typedef enum { T_id_already_exist, T_bad_arguments, T_cant_create_more } Type;
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
	
	class Item : Game_Object{
	private:
		int speed;
		bool cuttible;
		int price;
		string* resource;
	public:
		Item(Item& other) {
			this->speed = other.speed;
			this->cuttible = other.cuttible;
			this->price = other.price;
			this->resource = other.resource;
		}
		Item (string resource, string id = "", int speed = 0, bool cuttible = false, int price = 0)
			: speed(speed), cuttible(cuttible), price(price), Game_Object(id.c_str()) {
			this->resource = new string(resource);
			*this->resource = resource;
			//Game_Object(id.c_str());
		}
		~Item() override {
			delete this->resource;
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