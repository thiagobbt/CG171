#ifndef _DRAWING_MANAGER_H_
#define _DRAWING_MANAGER_H_

#include <cairo/cairo.h>
#include "Drawable.h"
#include "Window.h"

class DrawingManager {
 private:
 	cairo_surface_t* surface;
 	Window* my_window;
 protected:
 	DrawingManager() = default;
 public:
 	static DrawingManager& instance();
 	void draw(Drawable&);
 	void set_window(Window* w) { my_window = w; }
 	Window& window() { return *my_window; }
 	void setSurface(cairo_surface_t*);
 	void redraw();
};

#endif /* _DRAWING_MANAGER_H_ */