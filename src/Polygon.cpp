#include "Polygon.h"
#include "DrawingManager.h"
#include "PolygonGTK.h"
#include "utils.h"

Polygon::Polygon(const std::vector<Coordinate>& coordinates, utils::Color color, bool fill)
        : color(color), fill(fill) {
    world_loc = coordinates;
    drawable_obj = std::make_unique<PolygonGTK>(win_loc, color, fill);
}

void Polygon::draw() {
    DrawingManager::instance().draw(*drawable_obj);
}

void Polygon::clip() {
	Window::instance().clipPolygon(win_loc);
}
