/* copyright vfreitas & thiagobbt */

#ifndef POLYGON_H
#define POLYGON_H

#include "Object.h"
#include "DrawingManager.h"

class Polygon : public Object {
 private:
    Drawable* drawable_obj;
    std::vector<Coordinate> location;
    utils::Color color;
    bool fill;
 public:
    Polygon(std::vector<Coordinate>, utils::Color, bool);
    void draw();
};

#endif /* POLYGON_H */