/* copyright vfreitas & thiagobbt */

#ifndef _POINT_H_
#define _POINT_H_

#include "Object.h"
#include "DrawingManager.h"

class Point : public Object {
 private:
    utils::Color color;
 public:
    Point(const std::vector<Coordinate>&, utils::Color);
    void draw();
};

#endif /* POINT_H */