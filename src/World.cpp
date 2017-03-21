#include "World.h"

World::~World() {
	clear();
}

World& World::instance() {
	static World instance;
	return instance;
}

bool World::add_obj(string id, Object* obj) {

	if (!display_file.count(id)) {
		display_file[id] = obj;
		obj->draw();
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

void World::redraw() {
	for (auto obj : display_file) {
		obj.second->draw();
	}
}

void World::move_obj(string, const utils::Matrix&) {

}

void World::scale_obj(string, const utils::Matrix&) {

}

void World::rotate_obj(string, const utils::Matrix&, const Coordinate&, bool) {

}