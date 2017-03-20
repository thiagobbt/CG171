/* vfreitas & thiagobbt */

#include "Point.h"
#include "PointGTK.h"


Point::Point(std::vector<Coordinate> coordinates, utils::Color c) 
		: location(coordinates), color(c) {
	drawable_obj = new PointGTK(location, c, false);
}

Point::Point() {
	location = std::vector<Coordinate>(1);
}

void Point::transform(const utils::Matrix& m) {

}

void Point::draw() {
	DrawingManager::instance().draw(*drawable_obj);
}
