/* copyright vfreitas & thiagobbt */

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <vector>
#include "Coordinate.h"
#include "Drawable.h"

#include "gtk/gtk.h"

class Object {
 private:
 	Drawable drawable_obj;
 	std::vector<Coordinate> location;

 public:
  	//Object(std::vector<Coordinate>&) {}
 	virtual void draw() = 0;
};

#endif /* _OBJECT_H_ */