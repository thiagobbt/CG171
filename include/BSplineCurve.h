#ifndef BSPLINE_CURVE_H
#define BSPLINE_CURVE_H

#include <vector>
#include "Curve.h"

class BSplineCurve : public Curve {
 private:
    std::vector<Coordinate> original_loc;
    void update_coords();
    utils::Matrix mbs = {
        {-1.0/6, 1.0/2, -1.0/2, 1.0/6},
        {1.0/2, -1, 1.0/2, 0},
        {-1.0/2, 0, 1.0/2, 0},
        {1.0/6, 2.0/3, 1.0/6, 0}
    };
 public:
    BSplineCurve(const std::vector<Coordinate>& coordinates, utils::Color c);
    void draw();
};

#endif /* BSPLINE_CURVE_H */
