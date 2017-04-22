#include "Point.h"
#include "DrawingManager.h"
#include "PointGTK.h"
#include "utils.h"

Point::Point(const std::vector<Coordinate>& coordinates, utils::Color c) 
        : color(c) {
    world_loc = coordinates;
    drawable_obj = std::make_unique<PointGTK>(win_loc, c, false);
}

void Point::draw() {
    DrawingManager::instance().draw(*drawable_obj);
}

void Point::clip() {
    Window::instance().clipPoint(win_loc);
}
