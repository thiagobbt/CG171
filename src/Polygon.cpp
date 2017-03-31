#include "Polygon.h"
#include "PolygonGTK.h"

Polygon::Polygon(const std::vector<Coordinate>& coordinates, utils::Color color, bool fill)
		: color(color), fill(fill) {
	win_loc = new std::vector<Coordinate>();
	world_loc = new std::vector<Coordinate>(coordinates);
	drawable_obj = new PolygonGTK(win_loc, color, fill);
}

void Polygon::draw() {
	std::cout << "win_loc: " << std::endl;
	for (auto c : *win_loc) {
		std::cout << c << std::endl;
	}
	DrawingManager::instance().draw(*drawable_obj);
}
