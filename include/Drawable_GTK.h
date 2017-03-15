/* copyright vfreitas & thiagobbt */

#ifndef _DRAWABLE_GTK_H_
#define _DRAWABLE_GTK_H_

#include <vector>
#include <gtk/gtk.h>
#include "Drawable.h"
#include "Coordinate.h"
#include "DrawingManager.h"

class Drawable_GTK : Drawable {
 private:
 	
 public:
 	Drawable_GTK() = default;
 	Drawable_GTK(const Drawable_GTK&);
 	void draw(std::vector<Coordinate> &points, cairo_surface_t& surface, utils::Color& color, bool fill);
};

#endif /* _DRAWABLE_GTK_H_ */