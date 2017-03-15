#include "Line.h"
#include "LineGTK.h"
#include "DrawingManager.h"

Line::Line(std::vector<Coordinate>& a, utils::Color c) 
		: location(a), color(c) {
	drawable_obj = LineGTK(a, c, false); 
}

void Line::draw() {
	DrawingManager::instance().draw(drawable_obj);
}