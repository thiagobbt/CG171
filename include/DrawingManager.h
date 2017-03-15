/* copyright vfreitas & thiagobbt */

#ifndef _DRAWING_MANAGER_H_
#define _DRAWING_MANAGER_H_

#include "Drawable.h"

class DrawingManager {
 protected:
 	DrawingManager() = default;
 public:
 	static DrawingManager& instance();
 	void draw(Drawable&);
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