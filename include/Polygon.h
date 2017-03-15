/* copyright vfreitas & thiagobbt */

#ifndef POLYGON_H
#define POLYGON_H

#include "Object.h"
#include "DrawingManager.h"

class Polygon : Object {
 private:
    Drawable drawable_obj;
    std::vector<Coordinate> location;
    utils::Color color;
 public:
    Polygon(const std::vector<Coordinate>&);
    void draw();
};

#endif /* POLYGON_H */