/* vfreitas & thiagobbt */

#include "Point.h"


Point::Point(std::vector<Coordinate>& coordinates) {
	location = coordinates;
	//drawable_obj = Point_GTK(location);
}

Point::Point() {
	location = std::vector<Coordinate>(1);
}

void Point::draw() {
	//Control::mngr.draw(drawable_obj);
}