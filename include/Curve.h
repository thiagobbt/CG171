#ifndef CURVE_H
#define CURVE_H

#include <vector>
#include "Object.h"

class Curve : public Object {
 protected:
    utils::Color color;
 public:
    Curve(const std::vector<Coordinate>&, utils::Color);
    virtual void draw();
    void clip();
};

#endif /* CURVE_H */
