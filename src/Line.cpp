#include "Line.h"
#include "LineGTK.h"
#include "DrawingManager.h"

Line::Line(const std::vector<Coordinate>& a, utils::Color c) 
		: location(a), color(c) {
	std::cout << location[0].get_x() << " " << location[0].get_y() << "\n";
	//std:: cout << a[0].get_x() << " " << a[0].get_y() << "\n";
	drawable_obj = new LineGTK(location, c, false); 
}

void Line::draw() {
	std::cout << "line\n";
	std::cout << location[0].get_x() << " " << location[0].get_y() << "\n";
	std::cout << location[1].get_x() << " " << location[1].get_y() << "\n";
	DrawingManager::instance().draw(*drawable_obj);
}