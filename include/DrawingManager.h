/* copyright vfreitas & thiagobbt */

#ifndef _DRAWING_MANAGER_H_
#define _DRAWING_MANAGER_H_

#include <cairo/cairo.h>
#include "Drawable.h"

class DrawingManager {
 private:
 	cairo_surface_t* surface;
 protected:
 	DrawingManager() = default;
 public:
 	static DrawingManager& instance();
 	void draw(Drawable&);
 	void setSurface(cairo_surface_t*);
};


namespace utils {
	struct Color {
		double r, g, b, a;
	};
}

// namespace Control {
//  	DrawingManager mngr;
// }

#endif /* _DRAWING_MANAGER_H_ */