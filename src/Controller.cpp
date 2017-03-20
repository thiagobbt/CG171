#include "Controller.h"
#include "Coordinate.h"
#include "Point.h"
#include "Line.h"
#include "Polygon.h"



bool Controller::add_point(const string& id, double x, double y, utils::Color c) {
	Coordinate coord(x,y);
	return win.get_world().add_obj(id, new Point({coord}, c));
}

bool Controller::add_line(const string& id, double x1, double y1,
							double x2, double y2, utils::Color c) {

	Coordinate c1(x1,y1);
	Coordinate c2(x2,y2);
	std:: cout << c1.get_x() << " " << c1.get_y() << "\n";
	std:: cout << c2.get_x() << " " << c2.get_y() << "\n";
	std::cout << "red ctrl = " << c.r << std::endl;

	return win.get_world().add_obj(id, new Line({c1,c2},c));
}

bool Controller::add_polygon(const string& id, const std::vector<double>& locs,
							 utils::Color c, bool fill) {
	std::vector<Coordinate> coords;

	if (locs.size() % 2 == 0) {
		for (size_t i = 0; i < locs.size(); i += 2) {
			coords.push_back(Coordinate(locs[i], locs[i+1]));
		}
		win.get_world().add_obj(id, new Polygon(coords, c, fill));
	} else {
		return false;
	}

	return true;
}

void Controller::delete_obj(const string& key) {

	win.get_world().delete_obj(key);
}

void Controller::clear_world() {
	win.get_world().clear();
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