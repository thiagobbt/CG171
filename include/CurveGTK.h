#ifndef CURVE_GTK_H
#define CURVE_GTK_H

#include <vector>
#include <gtk/gtk.h>
#include "Drawable.h"
#include "Coordinate.h"
#include "Window.h"
#include "utils.h"

class CurveGTK : public Drawable {
 private:
    std::vector<Coordinate> &coords;
    const utils::Color color;

 public:
    CurveGTK(std::vector<Coordinate>&, utils::Color);
    void draw(cairo_surface_t&, Window&);
};

#endif /* CURVE_GTK_H */
