#include <memory>
#include "Polygon.h"
#include "PolygonGTK.h"
#include "DrawingManager.h"

Polygon::Polygon(const std::vector<Coordinate>& coordinates, utils::Color color, bool fill)
        : color(color), fill(fill) {
    world_loc = coordinates;
    drawable_obj = std::unique_ptr<PolygonGTK>(new PolygonGTK(win_loc, color, fill));
}

void Polygon::draw() {
    DrawingManager::instance().draw(*drawable_obj);
}
