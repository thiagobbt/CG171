#include "Polygon.h"
#include "PolygonGTK.h"

Polygon::Polygon(const std::vector<Coordinate>& coordinates, utils::Color color, bool fill)
		: color(color), fill(fill) {
	location = new std::vector<Coordinate>(coordinates);
	drawable_obj = new PolygonGTK(location, color, fill);
}

Polygon::~Polygon() {
	delete drawable_obj;
}

void Polygon::draw() {
	DrawingManager::instance().draw(*drawable_obj);
}
