/* vfreitas & thiagobbt */

#include "Point.h"
#include "PointGTK.h"


Point::Point(const std::vector<Coordinate>& coordinates, utils::Color c) 
		: color(c) {
	world_loc = new std::vector<Coordinate>(coordinates);
	drawable_obj = new PointGTK(world_loc, c, false);
}

void Point::draw() {
	DrawingManager::instance().draw(*drawable_obj);
}
