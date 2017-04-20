#include "CurveGTK.h"

CurveGTK::CurveGTK(std::vector<Coordinate>& coords, utils::Color c)
    : coords(coords), color(c) {}

void CurveGTK::draw(cairo_surface_t& surface, Window& win) {
    std::cout << "Curve::draw" << std::endl;
    Coordinate a = win.to_viewport(coords[0]);
    cairo_t *cr = cairo_create(&surface);
    cairo_set_source_rgb(cr, color.r, color.g, color.b);
    cairo_move_to(cr, a.get_x(), a.get_y());

    for (size_t i = 1; i < coords.size(); i++) {
        Coordinate b = win.to_viewport(coords[i]);
        cairo_line_to(cr, b.get_x(), b.get_y());
    }

    cairo_stroke(cr);
}
