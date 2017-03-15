#include "Controller.h"
#include "Coordinate.h"

bool Controller::add_point(const string& id, double x, double y, utils::Color c) {
	Coordinate coord(x,y,0,0);
	return world->add_obj(id, Point({coord}, c));
}

bool Controller::add_line(const string& id, double x1, double y1,
							double x2, double y2, utils::Color) {
	Coordinate c1(x1,y1,0,0);
	Coordinate c2(x2,y2,0,0);
	return world->add_obj(id, Line({c1,c2},c));
}

bool Controller::add_polygon(const string& id, const std::vector<double>& locs,
							 utils::Color c, bool fill) {
	std::vector<Coordinate> coords;
	if (locs.length() % 2) {
		for (size_t i = 0; i < locs.length(); locs += 2) {
			coords.emplace_back(locs[i], locs[i+1],0,0);
		}
		return world->add_obj(id, Polygon(coords, c, fill));
	} else {
		return false;
	}
}

void Controller::delete_obj(const string& key) {
	world->delete_obj(key);
}