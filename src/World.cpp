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
	Coordinate obj_center = display_file[id]->center();

	utils::Matrix translate(3, 3);
	translate(0, 0) = 1;
	translate(1, 1) = 1;
	translate(2, 2) = 1;
	translate(2, 0) = -obj_center.get_x();
	translate(2, 1) = -obj_center.get_y();

	utils::Matrix translate_back(3, 3);
	translate_back(0, 0) = 1;
	translate_back(1, 1) = 1;
	translate_back(2, 2) = 1;
	translate_back(2, 0) = obj_center.get_x();
	translate_back(2, 1) = obj_center.get_y();

	utils::Matrix scale = (translate * m) * translate_back;

	display_file[id]->transform(scale);
}

void World::rotate_obj(string id, utils::Matrix& m, Coordinate& coord, bool use_coord) {
	utils::Matrix translate(3, 3);
	utils::Matrix translate_back(3, 3);

	translate(0, 0) = 1;
	translate_back(0, 0) = 1;
	translate(1, 1) = 1;
	translate_back(1, 1) = 1;
	translate(2, 2) = 1;
	translate_back(2, 2) = 1;

	std::cout << "world::rotate_obj use_coord=" << use_coord << std::endl;

	if (use_coord) {
		translate(2, 0) = -coord.get_x();
		translate_back(2, 0) = coord.get_x();
		translate(2, 1) = -coord.get_y();
		translate_back(2, 1) = coord.get_y();
	} else {
		Coordinate obj_center = display_file[id]->center();
		translate(2, 0) = -obj_center.get_x();
		translate_back(2, 0) = obj_center.get_x();
		translate(2, 1) = -obj_center.get_y();
		translate_back(2, 1) = obj_center.get_y();
	}

	utils::Matrix rotate = (translate * m) * translate_back;

	display_file[id]->transform(rotate);
}