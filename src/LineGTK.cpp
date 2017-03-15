/* copyright vfreitas & thiagobbt */

#include "LineGTK.h"

LineGTK::LineGTK(std::vector<Coordinate>& coords, utils::Color color, bool fill) 
		: coords(coords), color(color), fill(fill) {}

void LineGTK::draw(cairo_surface_t& surface) {
    cairo_t *cr = cairo_create(&surface);
    cairo_set_source_rgb(cr, color.r, color.g, color.b);

    cairo_move_to(cr, coords[0].get_x(), coords[0].get_y());
    cairo_line_to(cr, coords[1].get_x(), coords[1].get_y());

    cairo_stroke(cr);
}
