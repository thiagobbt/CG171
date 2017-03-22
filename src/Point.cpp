/* vfreitas & thiagobbt */

#include "Point.h"
#include "PointGTK.h"


Point::Point(const std::vector<Coordinate>& coordinates, utils::Color c) 
		: color(c) {
	location = new std::vector<Coordinate>(coordinates);
	drawable_obj = new PointGTK(location, c, false);
}

Point::Point() {
	location = new std::vector<Coordinate>(1);
}

Point::~Point() {
	delete drawable_obj;
}

void Point::draw() {
	DrawingManager::instance().draw(*drawable_obj);
}
