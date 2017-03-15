/* copyright vfreitas & thiagobbt */

#ifndef _LINE_GTK_H_
#define _LINE_GTK_H_

#include <vector>
#include <gtk/gtk.h>
#include "Drawable_GTK.h"
#include "Coordinate.h"
#include "DrawingManager.h"

class LineGTK : Drawable_GTK {
 private:
 	std::vector<Coordinate>& coords;
 	const utils::Color& color;
 	const bool& fill;

 public:
    LineGTK(std::vector<Coordinate>&, utils::Color, bool);
    void draw(cairo_surface_t&);
};

#endif /* _LINE_GTK_H_ */
