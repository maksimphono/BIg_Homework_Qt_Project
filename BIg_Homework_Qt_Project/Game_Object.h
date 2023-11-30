#define GAME_OBJECT_H 0

#include <map>
#include <vector>
#include <ctime>

using std::map;
using std::vector;

typedef enum {T1} EventType;

typedef unsigned long long ull;

class Game_Event;

typedef void (*EventHandler)(Game_Event&);

namespace Game_Object_NS {
	using std::string;
	const unsigned ID_MAX_LEN = 20;
	class Game_Object;

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
	public:
		string id;
		string state;
		
		Game_Object(const char* id = "") {
			if (id != "" && !checkId(id)) {
				throw Exceptions::Exception_id_already_exist;
			}
			this->id = id;
			Game_Object_NS::objects[this->id] = this;
			this->state = "mounting";
			this->handlers = map<EventType, vector<EventHandler>>();
		}
		virtual ~Game_Object() {
			objects.erase(this->id);
		}
	public:
		int bind(EventType& type, EventHandler& handler) {
			this->handlers[type].push_back(handler);
			return this->handlers[type].size();
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