/* copyright vfreitas & thiagobbt */

#include <vector>
#include <gtk/gtk.h>
#include "Drawable_GTK.h"
#include "Coordinate.h"
#include "DrawingManager.h"

class PointGTK : Drawable_GTK {
 public:
    PointGTK();

    void draw(std::vector<Coordinate> &points, cairo_surface_t& surface, utils::Color& color, bool fill) {
    	cairo_t *cr = cairo_create(&surface);
        cairo_set_source_rgb(cr, color.r, color.g, color.b);

    	double x = points[0].get_x();
    	double y = points[0].get_y();

    	cairo_move_to(cr, x, y);
	    cairo_line_to(cr, x+1, y+1);
	    cairo_close_path(cr);
	    cairo_stroke(cr);
    }
};