#ifndef CURVE_H
#define CURVE_H

#include <vector>
#include "Object.h"

class Curve : public Object {
 protected:
    utils::Color color;
 public:
    virtual void draw() = 0;
    Drawable& drawable() { return *drawable_obj; }
    void clip();
};

#endif /* CURVE_H */
