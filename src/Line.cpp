#include "Line.h"
#include "DrawingManager.h"
#include "LineGTK.h"
#include "utils.h"

Line::Line(const std::vector<Coordinate>& coordinates, utils::Color c) 
        : color(c) {
    world_loc = coordinates;
    drawable_obj = std::make_unique<LineGTK>(win_loc, c, false);
}

void Line::draw() {
    DrawingManager::instance().draw(*drawable_obj);
}

void Line::clip() {
    Window::instance().clipLine(win_loc);
}
