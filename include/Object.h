/* copyright vfreitas & thiagobbt */

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <vector>
#include "Coordinate.h"
#include "Drawable.h"

class Object {
 private:
 	Drawable& drawable_obj;
 	std::vector<Coordinate&> location;

 public:
 	Object(const Object&);
 	Object(std::vector<Coordinate&>);
 	void draw();
};

#endif /* _OBJECT_H_ */