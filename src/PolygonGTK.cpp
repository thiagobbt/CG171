/* copyright vfreitas & thiagobbt */

#include "PolygonGTK.h"

PolygonGTK::PolygonGTK(std::vector<Coordinate>& coords, utils::Color color, bool fill) 
        : coords(coords), color(color), fill(fill) {}

void PolygonGTK::draw(cairo_surface_t& surface) {
    cairo_t *cr = cairo_create(&surface);
    cairo_set_source_rgb(cr, color.r, color.g, color.b);

    cairo_move_to(cr, coords[0].get_x(), coords[0].get_y());
    
    for (size_t i = 1; i < coords.size(); i++) {
        cairo_line_to(cr, coords[i].get_x(), coords[i].get_y());
    }

    if (fill) {
        cairo_fill(cr);
    } else {
        cairo_close_path(cr);
    }

    cairo_stroke(cr);
}