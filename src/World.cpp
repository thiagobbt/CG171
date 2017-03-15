#include "World.h"

bool World::add_object(string id, Object* obj) {
	if (!display_file.count(id)) {
		display_file[id] = obj;
		return true;
	} else {
		return false;
	}
}

void World::delete_object(string id) {
	display_file.erase(id);
}