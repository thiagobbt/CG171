#ifndef POINT_GTK_H
#define POINT_GTK_H

#include <vector>
#include <gtk/gtk.h>
#include "Drawable.h"
#include "Coordinate.h"
#include "Window.h"
#include "utils.h"

class PointGTK : public Drawable {
 private:
    std::vector<Coordinate> &coords;
    const utils::Color color;

 public:
    PointGTK(std::vector<Coordinate>&, utils::Color, bool);
    void draw(cairo_surface_t&, Window&);
};

#endif /* POINT_GTK_H */
