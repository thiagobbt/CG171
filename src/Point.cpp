#include <memory>
#include "Point.h"
#include "PointGTK.h"
#include "DrawingManager.h"

Point::Point(const std::vector<Coordinate>& coordinates, utils::Color c) 
        : color(c) {
    world_loc = coordinates;
    drawable_obj = std::unique_ptr<PointGTK>(new PointGTK(win_loc, c, false));
}

void Point::draw() {
    DrawingManager::instance().draw(*drawable_obj);
}
