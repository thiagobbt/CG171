/* copyright vfreitas & thiagobbt */

#ifndef LINE_H
#define LINE_H

#include "Object.h"

class Line : Object {
 private:
    Drawable& drawable_obj;
    std::vector<Coordinate> location;
 public:
    Line(const Coordinate&, const Coordinate&);
    void draw();
};

#endif /* LINE_H */