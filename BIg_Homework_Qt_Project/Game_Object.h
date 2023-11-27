#define GAME_OBJECT_H 0

#include <map>
#include <vector>

using std::map;
using std::vector;

typedef enum {T1} EventType;

typedef unsigned long long ull;

class Game_Event;

typedef void (*EventHandler)(Game_Event& evnt);

class Game_Object {
private:
	ull id;
	map<EventType, vector<EventHandler>> handlers;
public:
	Game_Object() : id(0) {}
};

class Game_Event {
private:
	EventType type;
	Game_Object target;
	ull tickstamp;
public:
};
