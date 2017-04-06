#ifndef POLYGON_GTK_H
#define POLYGON_GTK_H

#include <vector>
#include <gtk/gtk.h>
#include "Drawable.h"
#include "Coordinate.h"
#include "DrawingManager.h"

class PolygonGTK : public Drawable {
 private:
    std::vector<Coordinate> &coords;
    const utils::Color color;
    bool fill;

 public:
    PolygonGTK(std::vector<Coordinate>&, utils::Color, bool);
    void draw(cairo_surface_t&, Window&);
};

#endif /* POLYGON_GTK_H */
