#include "PointGTK.h"

PointGTK::PointGTK(std::vector<Coordinate>& coords, utils::Color color, bool /*fill*/)
        : coords(coords), color(color) {}

void PointGTK::draw(cairo_surface_t& surface, Window& win) {
    if (coords.empty()) return;
    Coordinate a = win.to_viewport(coords[0]);
    cairo_t *cr = cairo_create(&surface);
    cairo_set_source_rgb(cr, color.r, color.g, color.b);

    double x = a.get_x();
    double y = a.get_y();

    cairo_move_to(cr, x, y);
    cairo_line_to(cr, x+1, y+1);
    cairo_close_path(cr);
    cairo_stroke(cr);
}
