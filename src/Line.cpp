#include "Line.h"
#include "LineGTK.h"
#include "DrawingManager.h"

Line::Line(const std::vector<Coordinate>& a, utils::Color c) 
		: location(a), color(c) {
	std::cout << "red line = " << color.r << std::endl;
	drawable_obj = new LineGTK(location, c, false); 
}

void Line::transform(const utils::Matrix &) {
	
}

void Line::draw() {
	DrawingManager::instance().draw(*drawable_obj);
}
