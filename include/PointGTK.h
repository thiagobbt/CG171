/* copyright vfreitas & thiagobbt */

#ifndef _POINT_GTK_H_
#define _POINT_GTK_H_

#include <vector>
#include <gtk/gtk.h>
#include "Drawable_GTK.h"
#include "Coordinate.h"
#include "DrawingManager.h"

class PointGTK : public Drawable_GTK {
 private:
 	std::vector<Coordinate>& coords;
 	const utils::Color& color;

 public:
    PointGTK(std::vector<Coordinate>&, utils::Color, bool);
    void draw(cairo_surface_t&);
};

#endif /* _POINT_GTK_H_ */