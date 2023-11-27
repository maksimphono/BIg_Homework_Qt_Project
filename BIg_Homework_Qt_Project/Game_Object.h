#define GAME_OBJECT_H 0

#include <map>
#include <vector>
#include <ctime>

using std::map;
using std::vector;

typedef enum {T1} EventType;

typedef unsigned long long ull;

class Game_Event;

typedef void (*EventHandler)(Game_Event& evnt);

namespace Game_Object_NS {
	using std::string;
	const unsigned ID_MAX_LEN = 20;
	class Game_Object;

	map<string, Game_Object*> objects;

	class Game_Object {
	private:
		
		static char* newUniqueId() {
			ull t = (ull)time(NULL);
			char* timestamp = new char[ID_MAX_LEN];

			sprintf(timestamp, "%u", t);
			while (objects.find(timestamp) != objects.end()) {
				sprintf(timestamp, "%u", t);
				t++;
			}
			
			return timestamp;
		}

	private:
		
		map<EventType, vector<EventHandler>> handlers;
	public:
		char* id;
		static Game_Object* getElementById(char* id) {
			string id_str = string(id);
			if (objects.find(id_str) == objects.end()) return NULL;
			return objects[id_str];
		}
		Game_Object(char* id = NULL) : id(newUniqueId()) {
			Game_Object_NS::objects[this->id] = this;
		}
		virtual ~Game_Object() {
			objects.erase(this->id);
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


