#include <memory>
#include "Line.h"
#include "LineGTK.h"
#include "DrawingManager.h"

Line::Line(const std::vector<Coordinate>& coordinates, utils::Color c) 
        : color(c) {
    world_loc = coordinates;
    drawable_obj = std::unique_ptr<LineGTK>(new LineGTK(win_loc, c, false));
}

void Line::draw() {
    DrawingManager::instance().draw(*drawable_obj);
}
