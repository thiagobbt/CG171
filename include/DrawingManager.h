/* copyright vfreitas & thiagobbt */

#ifndef _DRAWING_MANAGER_H_
#define _DRAWING_MANAGER_H_

class DrawingManager {
 private:
 	
 public:
 	void draw(const Drawable&);
};


namespace utils {
	struct Color {
		double r, g, b, a;
	};
}

namespace Control {
 	DrawingManager mngr;
}

#endif /* _DRAWING_MANAGER_H_ */