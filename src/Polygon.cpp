#include "Polygon.h"
#include "PolygonGTK.h"
#include "DrawingManager.h"

Polygon::Polygon(const std::vector<Coordinate>& coordinates, utils::Color color, bool fill)
		: color(color), fill(fill) {
	win_loc = new std::vector<Coordinate>();
	world_loc = new std::vector<Coordinate>(coordinates);
	drawable_obj = new PolygonGTK(win_loc, color, fill);
}

void Polygon::draw() {
	DrawingManager::instance().draw(*drawable_obj);
}
