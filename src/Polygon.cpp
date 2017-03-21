#include "Polygon.h"
#include "PolygonGTK.h"

Polygon::Polygon(std::vector<Coordinate> location, 	utils::Color color, bool fill)
		: location(location), color(color), fill(fill) {
	drawable_obj = new PolygonGTK(location, color, fill);
}

Polygon::~Polygon() {
	delete drawable_obj;
}

void Polygon::draw() {
	DrawingManager::instance().draw(*drawable_obj);
}
