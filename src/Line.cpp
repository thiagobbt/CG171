#include "Line.h"
#include "LineGTK.h"
#include "DrawingManager.h"

Line::Line(const std::vector<Coordinate>& coordinates, utils::Color c) 
		: color(c) {
	world_loc = new std::vector<Coordinate>(coordinates);
	drawable_obj = new LineGTK(world_loc, c, false); 
}

void Line::draw() {
	DrawingManager::instance().draw(*drawable_obj);
}
