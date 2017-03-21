/* copyright vfreitas & thiagobbt */

#ifndef LINE_H
#define LINE_H

#include "Object.h"
#include "DrawingManager.h"

class Line : public Object {
 private:
    Drawable* drawable_obj;
    std::vector<Coordinate> location;
    utils::Color color;
 public:
    Line(const std::vector<Coordinate>&, utils::Color);
    ~Line();
    void draw();
};

#endif /* LINE_H */