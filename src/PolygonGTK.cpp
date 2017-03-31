/* copyright vfreitas & thiagobbt */

#include "PolygonGTK.h"

PolygonGTK::PolygonGTK(std::vector<Coordinate>* coords, utils::Color color, bool fill) 
        : coords(coords), color(color), fill(fill) {}

void PolygonGTK::draw(cairo_surface_t& surface, Window& win) {
    cairo_t *cr = cairo_create(&surface);
    cairo_set_source_rgb(cr, color.r, color.g, color.b);

    auto initial_point = win.to_viewport((*coords)[0]);
    std::cout << initial_point << std::endl;

    cairo_move_to(cr, initial_point.get_x(), initial_point.get_y());
    
    for (size_t i = 1; i < coords->size(); i++) {
        auto point = win.to_viewport((*coords)[i]);
        std::cout << point << std::endl;
        cairo_line_to(cr, point.get_x(), point.get_y());
    }

    if (fill) {
        cairo_fill(cr);
    } else {
        cairo_close_path(cr);
    }

    cairo_stroke(cr);
}
