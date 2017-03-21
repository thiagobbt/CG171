#include "Controller.h"
#include "Coordinate.h"
#include "Point.h"
#include "Line.h"
#include "Polygon.h"
#include <cmath>

#define PI 3.14159265

bool Controller::add_point(const string& id, double x, double y, utils::Color c) {
	Coordinate coord(x,y);
	return World::instance().add_obj(id, new Point({coord}, c));
}

bool Controller::add_line(const string& id, double x1, double y1,
							double x2, double y2, utils::Color c) {

	Coordinate c1(x1,y1);
	Coordinate c2(x2,y2);

	return World::instance().add_obj(id, new Line({c1,c2},c));
}

bool Controller::add_polygon(const string& id, const std::vector<double>& locs,
							 utils::Color c, bool fill) {
	std::vector<Coordinate> coords;

	if (locs.size() % 2 == 0) {
		for (size_t i = 0; i < locs.size(); i += 2) {
			coords.push_back(Coordinate(locs[i], locs[i+1]));
		}
		World::instance().add_obj(id, new Polygon(coords, c, fill));
	} else {
		return false;
	}

	return true;
}

void Controller::delete_obj(const string& key) {

	World::instance().delete_obj(key);
}

void Controller::clear_world() {
	World::instance().clear();
}

void Controller::zoom_in(double zoom) {
	win.zoom(zoom);
}


void Controller::zoom_out(double zoom) {
	win.zoom(1/zoom);
}

void Controller::pan_x(double x) {

	win.move(x,0,0);
}

void Controller::pan_y(double y) {
	win.move(0,y,0);
}

void Controller::move_obj(const string& id, double dx, double dy) {
	std::cout << "ctrl::move_obj id=" << id << std::endl;
	utils::Matrix *a = new utils::Matrix(3,3);
	a->fill(0);
	(*a)(0,0) = 1;
	(*a)(1,1) = 1;
	(*a)(2,2) = 1;
	(*a)(2,0) = dx;
	(*a)(2,1) = dy;
	World::instance().move_obj(id, *a);
}

void Controller::rotate_obj(const string& id, double teta, double x, double y, bool center) {
	utils::Matrix a(3,3);
	a.fill(0);
	auto angle = teta*PI/180;
	a(0,0) = cos(angle);
	a(0,1) = - sin(angle);
	a(1,0) = sin(angle);
	a(1,1) = cos(angle);
	a(2,2) = 1;
	Coordinate loc(x,y);
	World::instance().rotate_obj(id, a, loc, center);
} 

void Controller::scale_obj(const string& id, double sx, double sy) {
 	utils::Matrix a(3,3);
	a.fill(0);
	a(0,0) = sx;
	a(1,1) = sy;
	a(2,2) = 1;
	World::instance().scale_obj(id, a);
}