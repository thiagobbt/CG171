/* vfreitas & thiagobbt */

#include "Point.h"


Point::Point(std::vector<Coordinate>& coordinates, utils::Color c) 
		: location(coordinates), color(c) {
	drawable_obj = Point_GTK(location, c, false);
}

Point::Point() {
	location = std::vector<Coordinate>(1);
}

void Point::draw() {
	DrawingManager::instance().draw(drawable_obj);
}