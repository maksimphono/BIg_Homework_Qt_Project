#pragma once
#include "Game_Object.h"
#include <string>

namespace Structure_NS {
	using std::vector;
	using std::string;
	using std::map;
	using namespace Game_Object_NS;

	typedef enum {UP, DOWN, LEFT, RIGHT} Orientation;

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

	class Structure : Game_Object {
	private:
		bool enabled;
		Orientation orientation;
	public:
		Structure(Structure& other) {
			this->orientation = other.orientation;
			this->enabled = true;
		}
		Structure(Orientation orientation, string id)
			: orientation(orientation), Game_Object(id.c_str()) {
		}
		~Structure() override {
		}
	public: // getters:
		int getOrientation() const {
			return this->orientation;
		}
		bool isEnabled() const {
			return this->enabled;
		}
	public: // setters:
		void disable() {
			this->enabled = false;
		}
		void enable() {
			this->enabled = true;
		}
	};
}