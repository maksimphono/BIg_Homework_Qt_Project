#define GAME_OBJECT_H 0

#include <map>
#include <vector>

using std::map;
using std::vector;

typedef enum {T1} EventType;

typedef unsigned long long ull;

class Game_Event;

typedef void (*EventHandler)(Game_Event& evnt);

namespace Game_Object_NS {
	class Game_Object;

	vector<Game_Object*> objects;

	class Game_Object {
	private:
		
		static ull newUniqueId() {
			return objects.size();
		}
		
		
	private:
		
		map<EventType, vector<EventHandler>> handlers;
	public:
		ull id;
		static Game_Object& getElementById(ull id) {
			return *objects[id];
		}
		Game_Object() : id(newUniqueId()) {
			Game_Object_NS::objects.push_back(this);
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


