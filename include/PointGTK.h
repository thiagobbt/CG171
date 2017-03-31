#ifndef _POINT_GTK_H_
#define _POINT_GTK_H_

#include <vector>
#include <gtk/gtk.h>
#include "Drawable.h"
#include "Coordinate.h"
#include "Window.h"
#include "utils.h"

class PointGTK : public Drawable {
 private:
 	std::vector<Coordinate> *coords;
 	const utils::Color color;

 public:
    PointGTK(std::vector<Coordinate>*, utils::Color, bool);
    void draw(cairo_surface_t&, Window&);
};

#endif /* _POINT_GTK_H_ */
