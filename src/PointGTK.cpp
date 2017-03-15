/* copyright vfreitas & thiagobbt */

#include "PointGTK.h"

PointGTK::PointGTK(std::vector<Coordinate>& coords, utils::Color color, bool fill) 
        : coords(coords), color(color) {}

void PointGTK::draw(cairo_surface_t& surface) {
    cairo_t *cr = cairo_create(&surface);
    cairo_set_source_rgb(cr, color.r, color.g, color.b);

    double x = coords[0].get_x();
    double y = coords[0].get_y();

    cairo_move_to(cr, x, y);
    cairo_line_to(cr, x+1, y+1);
    cairo_close_path(cr);
    cairo_stroke(cr);
}
