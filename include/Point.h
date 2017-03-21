/* copyright vfreitas & thiagobbt */

#ifndef _POINT_H_
#define _POINT_H_

#include "Object.h"
#include "DrawingManager.h"

class Point : public Object {
 private:
    utils::Color color;
 public:
    Point(std::vector<Coordinate>, utils::Color);
    Point();
    ~Point();
    void draw();
};

#endif /* POINT_H */