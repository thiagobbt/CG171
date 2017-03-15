/* copyright vfreitas & thiagobbt */

#ifndef _POINT_H_
#define _POINT_H_

#include "Object.h"
#include "DrawingManager.h"

class Point : Object {
 private:
    Drawable drawable_obj;
    std::vector<Coordinate> location;
 public:
    Point(std::vector<Coordinate>&);
    Point();
    void draw();
};

#endif /* POINT_H */