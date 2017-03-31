/* copyright vfreitas & thiagobbt */

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <vector>
#include "utils.h"
#include "Coordinate.h"
#include "Drawable.h"

#include "gtk/gtk.h"

class Object {
 protected:
 	Drawable* drawable_obj;
 	std::vector<Coordinate> *world_loc;
 	std::vector<Coordinate> *win_loc;

 public:
  	//Object(std::vector<Coordinate>&) {}
  	~Object();
 	virtual void draw() = 0;
  	void transform(utils::Matrix&); // Translação (0,1), Escalonamento (2,5), Rotação (6)
  	Coordinate center();
  	void update(const utils::Matrix& m);
};

#endif /* _OBJECT_H_ */