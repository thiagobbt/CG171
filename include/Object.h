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
 	virtual void draw() = 0;
  	void transform(const utils::Matrix&); // Translação (0,1), Escalonamento (2,5), Rotação (6)
};

#endif /* _OBJECT_H_ */