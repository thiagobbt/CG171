/* copyright vfreitas & thiagobbt */

#include <vector>
#include <gtk/gtk.h>
#include "Drawable_GTK.h"
#include "Coordinate.h"

class PolygonGTK : Drawable_GTK {
 public:
    PolygonGTK();

    void draw(std::vector<Coordinate> &points, cairo_surface_t& surface, GdkRGBA& color, bool fill) {
        cairo_t *cr = cairo_create(&surface);
        gdk_cairo_set_source_rgba(cr, &color);

        cairo_move_to(cr, points[0].get_x(), points[0].get_y());
        
        for (size_t i = 1; i < points.size(); i++) {
            cairo_line_to(cr, points[i].get_x(), points[i].get_y());
        }

        if (fill) {
            cairo_fill(cr);
        } else {
            cairo_close_path(cr);
        }

        cairo_stroke(cr);
    }
};
