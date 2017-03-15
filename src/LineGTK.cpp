/* copyright vfreitas & thiagobbt */

#include <vector>
#include <gtk/gtk.h>
#include "Drawable_GTK.h"
#include "Coordinate.h"

class LineGTK : Drawable_GTK {
 public:
    LineGTK();

    void draw(std::vector<Coordinate> &points, cairo_surface_t& surface, GdkRGBA& color, bool fill) {
        cairo_t *cr = cairo_create(&surface);
        gdk_cairo_set_source_rgba(cr, &color);

        cairo_move_to(cr, points[0].get_x(), points[0].get_y());
        cairo_line_to(cr, points[1].get_x(), points[1].get_y());

        cairo_stroke(cr);
    }
};
