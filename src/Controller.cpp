#include "Controller.h"
#include "Coordinate.h"
#include "Point.h"
#include "Line.h"
#include "Polygon.h"
#include "utils.h"
#include <cmath>
#include <cassert>

bool Controller::add_point(const string& id, double x, double y, utils::Color c) {
	Coordinate coord(x,y);
	bool res = World::instance().add_obj(id, new Point({coord}, c));
	if (res) World::instance().update_obj(id);
	return res;
}

bool Controller::add_line(const string& id, double x1, double y1,
							double x2, double y2, utils::Color c) {

	Coordinate c1(x1,y1);
	Coordinate c2(x2,y2);

	bool res = World::instance().add_obj(id, new Line({c1,c2},c));
	if (res) World::instance().update_obj(id);
	return res;
}

bool Controller::add_polygon(const string& id, const std::vector<double>& locs,
							 utils::Color c, bool fill) {
	std::vector<Coordinate> coords;

	assert(locs.size() % 2 == 0);

	for (size_t i = 0; i < locs.size(); i += 2) {
		coords.push_back(Coordinate(locs[i], locs[i+1]));
	}

	bool res = World::instance().add_obj(id, new Polygon(coords, c, fill));
	if (res) World::instance().update_obj(id);
	return res;
}

void Controller::delete_obj(const string& key) {
	World::instance().delete_obj(key);
}

void Controller::clear_world() {
	World::instance().clear();
}

void Controller::zoom_in(double zoom) {
	Window::instance().zoom(zoom);
	World::instance().update_all();
}


void Controller::zoom_out(double zoom) {
	Window::instance().zoom(1/zoom);
	World::instance().update_all();
}

void Controller::pan_x(double x) {
	Window::instance().move(x,0,0);
	World::instance().update_all();
}

void Controller::pan_y(double y) {
	Window::instance().move(0,y,0);
	World::instance().update_all();
}

void Controller::rotate(double theta) {
	Window::instance().rotate(theta);
	World::instance().update_all();
}

void Controller::move_obj(const string& id, double dx, double dy) {
	auto a = utils::Transformation2D::translation_matrix(dx, dy);
	World::instance().move_obj(id, a);
}

void Controller::rotate_obj(const string& id, double theta, double x, double y, bool use_cord) {
	auto a = utils::Transformation2D::rotation_matrix(theta);
	Coordinate loc(x, y);
	World::instance().rotate_obj(id, a, loc, use_cord);
} 

void Controller::scale_obj(const string& id, double sx, double sy) {
 	auto a = utils::Transformation2D::scaling_matrix(sx, sy);
	World::instance().scale_obj(id, a);
	World::instance().update_obj(id);
}