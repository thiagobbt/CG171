#include "Polygon.h"
#include "PolygonGTK.h"

Polygon::Polygon(std::vector<Coordinate> coordinates, utils::Color color, bool fill)
		: color(color), fill(fill) {
	location = coordinates;
	drawable_obj = new PolygonGTK(coordinates, color, fill);
}

Polygon::~Polygon() {
	delete drawable_obj;
}

void Polygon::draw() {
	DrawingManager::instance().draw(*drawable_obj);
}
