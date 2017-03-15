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
	return win.get_world().add_obj(id, new Line({c1,c2},c));
}

bool Controller::add_polygon(const string& id, const std::vector<double>& locs,
							 utils::Color c, bool fill) {
	std::vector<Coordinate> coords;
	if (locs.size() % 2) {
		for (size_t i = 0; i < locs.size(); i += 2) {
			coords.push_back(Coordinate(locs[i], locs[i+1]));
			// coords.emplace_back(locs[i], locs[i+1],0,0);
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