#pragma once
#define GAME_OBJECT_H 0

#include <map>
#include <vector>
#include <ctime>

typedef enum {NONE, T1} EventType;

typedef unsigned long long ull;

class Game_Event;

namespace Game_Object_NS {
	using std::string;
	using std::map;
	using std::vector;
	const unsigned ID_MAX_LEN = 20;
	const string STATE_AFTER_INITIALIZATION = "mounting";
	class Game_Object;
	class Game_Event;
	typedef void (*EventHandler)(Game_Event* evnt);

	namespace Exceptions {
		typedef enum { T_id_already_exist , T_bad_arguments, T_cant_create_more} Type;
		class Exception : public std::exception {
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
		Exception Exception_id_already_exist(T_id_already_exist, "Error, object with specified id already exist!\n");
		Exception Exception_bad_arguments(T_bad_arguments, "Error, bad arguments!\n");
		Exception Exception_cant_create_more(T_cant_create_more, "Error, can't create more objects!\n");
	};

	map<string, Game_Object*> objects;

	class Game_Object {
	private:
		
		static bool checkId(string id) {
			return objects.find(id) == objects.end();
		}

	public:
		static Game_Object* getElementById(string id) {
			if (objects.find(id) == objects.end()) return NULL;
			return objects[id];
		}

	private:
		
		map<EventType, vector<EventHandler>*>* handlers;
		
	public: // basic data:
		string* id;
		string* state;
		
		Game_Object(const char* id = "") {
			if (id != "" && !checkId(id)) {
				throw Exceptions::Exception_id_already_exist;
			}
			this->id = new string(id);
			Game_Object_NS::objects[*this->id] = this;
			this->state = new string(STATE_AFTER_INITIALIZATION);
			this->handlers = new map<EventType, vector<EventHandler>*>();
		}
		virtual ~Game_Object() {
			objects.erase(*this->id);
			this->unbindAll();
			delete this->handlers;
			delete this->id;
			delete this->state;
		}

		virtual void tick(ull globalTick);

	public: // event methods:
		int bind(const EventType type, EventHandler handler) {
			if ((*this->handlers)[type] == NULL) (*this->handlers)[type] = new vector<EventHandler>();
			((*this->handlers)[type])->push_back(handler);
			return this->handlers[type].size() - 1;
		}
		void fireSeries(const EventType type, Game_Event* evnt) {
			if (!(*this->handlers)[type]) return;
			auto handlers = (*this->handlers)[type];
			for (const auto& handler : *handlers) {
				handler(evnt);
			}
		}
		void fireSingle(const EventType type, int index, Game_Event* evnt) {
			if (!(*this->handlers)[type]) return;

			auto handlers = (*this->handlers)[type];
			if (index <= handlers->size()) {
				(*handlers)[index](evnt);
			}
		}
		void fire(const EventType type, EventHandler handler, Game_Event* evnt) {
			if (!(*this->handlers)[type]) return;

			auto handlers = (*this->handlers)[type];
			for (const auto& my_handler : *handlers) {
				if (handler == my_handler) {
					handler(evnt);
				}
			}
		}
		void unbind(const EventType type, int index) {
			if (!(*this->handlers)[type]) return;
			if (index <= (*this->handlers)[type]->size()) {
				(*this->handlers)[type]->erase((*this->handlers)[type]->begin() + index);
			}
		}
		void unbind(const EventType type, EventHandler handler) {
			if (!(*this->handlers)[type]) return;

			typedef std::vector<Game_Object_NS::EventHandler>::iterator Iterator;

			auto& handlers = (*this->handlers)[type];
			vector<Iterator> indices = {};
			int deleted = 0;
			for (auto my_handler = handlers->begin(); my_handler < handlers->end(); my_handler++) {
				if (handler == *my_handler) {
					handlers->erase(my_handler);
					break;
				}
			}
		}
		void unbindAll() {
			for (const auto& handlers : (*this->handlers)) {
				if (!(handlers.second)) continue;
				for (int i = 0; i < handlers.second->size(); i++) {
					this->unbind(handlers.first, i);
					i--;
				}
			}
		}
	public: // getters:
		string getId() const{
			return *this->id;
		}
		string getState() const {
			return *this->id;
		}
	public: // setters:
		void setId(const string newId){
			if (Game_Object::checkId(newId)) {
				*this->id = newId;
			}
			else {
				throw Exceptions::Exception_id_already_exist;
			}
		}
		void setState(string newStatus) {
			*this->state = newStatus;
		}
	};

	class Game_Event {
	private:
		EventType type;
	public:
		ull tickstamp;
		Game_Object* target;
		Game_Object* object;
		void* payload;
	public:
		Game_Event() 
			: type(NONE), target(NULL), object(NULL), payload(NULL), tickstamp(0) {}
		Game_Event(Game_Event& another) 
			: type(another.type), target(another.target), object(another.object), payload(another.payload), tickstamp(another.tickstamp) {}
		Game_Event(const EventType type, Game_Object* target = NULL, Game_Object* object = NULL, void* payload = NULL, ull tickstamp = 0)
			: type(type), target(target), object(object), payload(payload), tickstamp(tickstamp) {}
		virtual ~Game_Event() {
			this->type = NONE;
			this->target = NULL;
			this->object = NULL;
			this->payload = NULL;
			this->tickstamp = 0;
		}
	};
}