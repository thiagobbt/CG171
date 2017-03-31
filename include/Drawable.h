#ifndef _DRAWABLE_H_
#define _DRAWABLE_H_

#include <gtk/gtk.h>

class Window;

class Drawable {
 private:
 	
 public:
 	Drawable() = default;
 	Drawable(const Drawable&);
 	virtual ~Drawable() {}
 	virtual void draw(cairo_surface_t& surface, Window&) = 0;
};

#endif /* _DRAWABLE_GTK_H_ */