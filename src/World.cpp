#include "World.h"

World::~World() {
	clear();
}

bool World::add_obj(string id, Object* obj) {
	if (!display_file.count(id)) {
		display_file[id] = obj;
		return true;
	} else {
		return false;
	}
}

void World::delete_obj(string id) {
	display_file.erase(id);
}

void World::clear() {
	for (auto obj : display_file) {
		delete obj.second;
	}
	display_file.clear();
}

