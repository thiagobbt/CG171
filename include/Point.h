#ifndef POINT_H
#define POINT_H

#include "Object.h"
#include "utils.h"

class Point : public Object {
 private:
    utils::Color color;

 public:
    Point(const std::vector<Coordinate>&, utils::Color);
    void draw();
};

#endif /* POINT_H */
