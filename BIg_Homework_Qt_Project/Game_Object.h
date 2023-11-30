#define GAME_OBJECT_H 0

#include <map>
#include <vector>
#include <ctime>

using std::map;
using std::vector;

typedef enum {T1} EventType;

typedef unsigned long long ull;

class Game_Event;

namespace Game_Object_NS {
	using std::string;
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
		
		map<EventType, vector<EventHandler>> handlers;
	public: // basic data:
		string id;
		string state;
		
		Game_Object(const char* id = "") {
			if (id != "" && !checkId(id)) {
				throw Exceptions::Exception_id_already_exist;
			}
			this->id = id;
			Game_Object_NS::objects[this->id] = this;
			this->state = STATE_AFTER_INITIALIZATION;
			this->handlers = map<EventType, vector<EventHandler>>();
		}
		virtual ~Game_Object() {
			objects.erase(this->id);
		}
	public: // event methods:
		int bind(const EventType type, EventHandler handler) {
			this->handlers[type].push_back(handler);
			return this->handlers[type].size() - 1;
		}
		void fireSeries(const EventType type, Game_Event* evnt) {
			auto handlers = this->handlers[type];
			for (const auto& handler : handlers) {
				handler(evnt);
			}
		}
		void fireSingle(const EventType type, int index, Game_Event* evnt) {
			auto handlers = this->handlers[type];
			if (index <= handlers.size()) {
				handlers[index](evnt);
			}
		}
		void unbind(const EventType type, int index) {
			if (index <= this->handlers[type].size()) {
				this->handlers[type].erase(this->handlers[type].begin() + index);
			}
		}
	public: // getters:
		string getId() const{
			return this->id;
		}
		string getState() const {
			return this->id;
		}
	public: // setters:
		void getId(const string newId){
			if (Game_Object::checkId(newId)) {
				this->id = newId;
			}
			else {
				throw Exceptions::Exception_id_already_exist;
			}
		}
		void getState(string newStatus) {
			this->state = newStatus;
		}
	};

	class Game_Event {
	private:
		EventType type;
		Game_Object target;
		ull tickstamp;
	public:
	};
}