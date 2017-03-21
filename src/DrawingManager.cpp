#include "DrawingManager.h"

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
