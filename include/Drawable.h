#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <gtk/gtk.h>

class Window;

class Drawable {
 public:
    Drawable() = default;
    Drawable(const Drawable&);
    virtual ~Drawable() {}
    virtual void draw(cairo_surface_t& surface, Window&) = 0;
};

#endif /* DRAWABLE_H */