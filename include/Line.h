/* copyright vfreitas & thiagobbt */

#ifndef LINE_H
#define LINE_H

#include "Object.h"
#include "DrawingManager.h"

class Line : Object {
 private:
    Drawable drawable_obj;
    std::vector<Coordinate> location;
    utils::Color color;
 public:
    Line(std::vector<Coordinate>&, utils::Color);
    void draw();
};

#endif /* LINE_H */