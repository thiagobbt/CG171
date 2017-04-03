#ifndef LINE_GTK_H
#define LINE_GTK_H

#include <vector>
#include <gtk/gtk.h>
#include "Drawable.h"
#include "Coordinate.h"
#include "Window.h"
#include "utils.h"

class LineGTK : public Drawable {
 private:
    std::vector<Coordinate> &coords;
    const utils::Color color;

 public:
    LineGTK(std::vector<Coordinate>&, utils::Color, bool);
    void draw(cairo_surface_t&, Window&);
};

#endif /* LINE_GTK_H */
