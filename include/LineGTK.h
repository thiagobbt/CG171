/* copyright vfreitas & thiagobbt */

#ifndef _LINE_GTK_H_
#define _LINE_GTK_H_

#include <vector>
#include <gtk/gtk.h>
#include "Drawable.h"
#include "Coordinate.h"
#include "DrawingManager.h"

class LineGTK : public Drawable {
 private:
 	std::vector<Coordinate> *coords;
 	const utils::Color color;

 public:
    LineGTK(std::vector<Coordinate>*, utils::Color, bool);
    void draw(cairo_surface_t&, Window&);
};

#endif /* _LINE_GTK_H_ */
