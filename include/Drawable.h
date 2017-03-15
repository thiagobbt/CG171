/* copyright vfreitas & thiagobbt */

#ifndef _DRAWABLE_H_
#define _DRAWABLE_H_

#include <vector>
#include <gtk/gtk.h>
#include "Coordinate.h"

class Drawable {
 private:
 	
 public:
 	Drawable() = default;
 	Drawable(const Drawable&);
 	virtual ~Drawable() {}
 	virtual void draw(cairo_surface_t& surface) = 0;
};

#endif /* _DRAWABLE_GTK_H_ */