#ifndef POLYGON_H
#define POLYGON_H

#include "Object.h"
#include "DrawingManager.h"

class Polygon : public Object {
 private:
    utils::Color color;
    bool fill;

 public:
    Polygon(const std::vector<Coordinate>&, utils::Color, bool);
    void draw();
    void clip();
};

#endif /* POLYGON_H */
