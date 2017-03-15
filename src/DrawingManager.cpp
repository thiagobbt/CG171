#include "DrawingManager.h"
#include "Callbacks.h"

DrawingManager& DrawingManager::instance() {
	static DrawingManager instance;
	return instance;
}

void DrawingManager::draw(Drawable& drawable) {
	drawable.draw();
}