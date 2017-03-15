/* copyright vfreitas & thiagobbt */

#ifndef _POINT_GTK_H_
#define _POINT_GTK_H_

#include <vector>
#include <gtk/gtk.h>
#include "Drawable_GTK.h"
#include "Coordinate.h"

class PointGTK : Drawable_GTK {
 public:
    PointGTK();

    void draw(std::vector<Coordinate> &points, cairo_surface_t& surface, GdkRGBA& color, bool fill) {
    	cairo_t *cr = cairo_create(&surface);
    	gdk_cairo_set_source_rgba(cr, &color);

    	double x = points[0].get_x();
    	double y = points[0].get_y();

    	cairo_move_to(cr, x, y);
	    cairo_line_to(cr, x+1, y+1);
	    cairo_close_path(cr);
	    cairo_stroke(cr);
    }
};

#endif /* POINT_GTK_H_ */