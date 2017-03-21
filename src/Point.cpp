/* vfreitas & thiagobbt */

#include "Point.h"
#include "PointGTK.h"


Point::Point(std::vector<Coordinate> coordinates, utils::Color c) 
		: color(c) {
	location = coordinates;
	drawable_obj = new PointGTK(location, c, false);
}

Point::Point() {
	location = std::vector<Coordinate>(1);
}

Point::~Point() {
	delete drawable_obj;
}

void Point::draw() {
	DrawingManager::instance().draw(*drawable_obj);
}
