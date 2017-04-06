#include "DrawingManager.h"
#include "World.h"
#include <gtk/gtk.h>

DrawingManager& DrawingManager::instance() {
    static DrawingManager instance;
    return instance;
}

void DrawingManager::draw(Drawable& drawable) {
    drawable.draw(*surface, window());
}

void DrawingManager::setSurface(cairo_surface_t* s) {
    surface = s;
}

void DrawingManager::redraw() {
    World::instance().redraw();
}

void DrawingManager::draw_viewport(std::vector<Coordinate>& coords) {
	cairo_t *cr = cairo_create(surface);
    cairo_set_source_rgb(cr, 0, 0, 0);

    auto initial_point = coords[0];

    cairo_move_to(cr, initial_point.get_x(), initial_point.get_y());

    for (size_t i = 1; i < coords.size(); i++) {
        auto point = coords[i];
        cairo_line_to(cr, point.get_x(), point.get_y());
    }

    cairo_close_path(cr);
    cairo_stroke(cr);
}
