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

void World::move_obj(string id, utils::Matrix& m) {
	std::cout << "world::move_obj id=" << id << std::endl;
	display_file[id]->transform(m);
}

void World::scale_obj(string id, utils::Matrix& m) {
	display_file[id]->transform(m);
}

void World::rotate_obj(string id, utils::Matrix& m, const Coordinate& coord, bool use_coord) {

}