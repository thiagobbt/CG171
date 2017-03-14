/* copyright vfreitas & thiagobbt */

#ifndef _POINT_H_
#define _POINT_H_

#include "Object.h"

class Point : Object {
 private:
    Drawable& drawable_obj;
    std::vector<Coordinate&> location;
 public:
    Point(const Point&);
    Point(Coordinate&);
    void draw();
};

#endif /* POINT_H */