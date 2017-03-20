/* copyright vfreitas & thiagobbt */

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <vector>
#include "utils.h"
#include "Coordinate.h"
#include "Drawable.h"

#include "gtk/gtk.h"

class Object {
 private:
 	Drawable* drawable_obj;
 	std::vector<Coordinate> location;

 public:
  	//Object(std::vector<Coordinate>&) {}
  	virtual ~Object() { delete drawable_obj; }
  	virtual void transform(const utils::Matrix&) = 0; // Translação (0,1), Escalonamento (2,5), Rotação (6)
 	virtual void draw() = 0;
};

#endif /* _OBJECT_H_ */