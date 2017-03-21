#include "Line.h"
#include "LineGTK.h"
#include "DrawingManager.h"

Line::Line(const std::vector<Coordinate>& coordinates, utils::Color c) 
		: color(c) {
	location = coordinates;
	drawable_obj = new LineGTK(location, c, false); 
}

Line::~Line() {
	delete drawable_obj;
}

void Line::draw() {
	DrawingManager::instance().draw(*drawable_obj);
}
