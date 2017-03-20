/* copyright vfreitas & thiagobbt */

#include "LineGTK.h"
#include "Window.h"

LineGTK::LineGTK(const std::vector<Coordinate>& coords, utils::Color c, bool fill) 
		: coords(coords), color(c) {}

void LineGTK::draw(cairo_surface_t& surface, Window& win) {
	Coordinate a = win.to_viewport(coords[0]);
	Coordinate b = win.to_viewport(coords[1]);

	std::cout << "red linegtk draw = " << color.r << std::endl;
	
	// std:: cout << "linegtk\n";
	// std:: cout << coords[0].get_x() << " " << coords[0].get_y() << "\n";
	// std:: cout << coords[1].get_x() << " " << coords[1].get_y() << "\n";
	// std:: cout << "linegtk\n";
    cairo_t *cr = cairo_create(&surface);
    cairo_set_source_rgb(cr, color.r, color.g, color.b);

    cairo_move_to(cr, a.get_x(), a.get_y());
    cairo_line_to(cr, b.get_x(), b.get_y());

    cairo_stroke(cr);
}
