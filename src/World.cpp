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
		// obj->draw();
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
	if (display_file.count(id) == 0) return;

	std::cout << "world::move_obj id=" << id << std::endl;
	display_file[id]->transform(m);
}

void World::scale_obj(string id, utils::Matrix& m) {
	if (display_file.count(id) == 0) return;

	Coordinate obj_center = display_file[id]->center();

	auto translate = utils::Transformation2D::translation_matrix(-obj_center.get_x(), -obj_center.get_y());
	auto translate_back = utils::Transformation2D::translation_matrix(obj_center.get_x(), obj_center.get_y());

	utils::Matrix scale = (translate * m) * translate_back;

	display_file[id]->transform(scale);
}

void World::rotate_obj(string id, utils::Matrix& m, Coordinate& coord, bool use_coord) {
	if (display_file.count(id) == 0) return;

	utils::Matrix translate(3, 3);
	utils::Matrix translate_back(3, 3);

	std::cout << "world::rotate_obj use_coord=" << use_coord << std::endl;

	if (use_coord) {
		translate = utils::Transformation2D::translation_matrix(-coord.get_x(), -coord.get_y());
		translate_back = utils::Transformation2D::translation_matrix(coord.get_x(), coord.get_y());
	} else {
		Coordinate obj_center = display_file[id]->center();
		translate = utils::Transformation2D::translation_matrix(-obj_center.get_x(), -obj_center.get_y());
		translate_back = utils::Transformation2D::translation_matrix(obj_center.get_x(), obj_center.get_y());
	}

	utils::Matrix rotate = (translate * m) * translate_back;

	display_file.at(id)->transform(rotate);
}

void World::update_obj(string id, const utils::Matrix& m) {
	if (display_file.count(id) == 0) return;

	display_file[id]->update(m);
}

void World::update_all(const utils::Matrix& m) {
	for (auto obj : display_file) {
		obj.second->update(m);
	}
}
