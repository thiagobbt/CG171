/* copyright vfreitas & thiagobbt */

#ifndef POLYGON_H
#define POLYGON_H

#include "Object.h"

class Polygon : Object {
 private:
    Drawable& drawable_obj;
    std::vector<Coordinate&> location;
 public:
    Polygon(const Polygon&);
    Polygon(const std::vector<Coordinate&>&);
    void draw();
};

#endif /* POLYGON_H */