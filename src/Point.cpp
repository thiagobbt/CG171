#include "Point.h"
#include "PointGTK.h"
#include "DrawingManager.h"

Point::Point(const std::vector<Coordinate>& coordinates, utils::Color c) 
        : color(c) {
    win_loc = new std::vector<Coordinate>();
    world_loc = new std::vector<Coordinate>(coordinates);
    drawable_obj = new PointGTK(win_loc, c, false);
}

void Point::draw() {
    DrawingManager::instance().draw(*drawable_obj);
}
