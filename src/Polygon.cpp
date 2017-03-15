#include "Polygon.h"

Polygon::Polygon(std::vector<Coordinate>& location, 
	utils::Color color, bool fill) : location(location), color(color),
	fill(fill) {
		drawable_obj = PolygonGTK(location, color, fill);
}

void Polygon::draw() {
	DrawingManager::instance().draw(drawable_obj);
}