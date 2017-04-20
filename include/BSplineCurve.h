#ifndef BSPLINE_CURVE_H
#define BSPLINE_CURVE_H

#include <vector>
#include "Curve.h"

class BSplineCurve : public Curve {
 private:
    std::vector<Coordinate> original_loc;
    void update_coords();
    const utils::Matrix mb = (utils::Matrix){
        {-1/6, 0.5, -0.5, 1/6},
        {0.5, -1, 0.5, 0},
        {-0.5, 0, 0.5, 0},
        {1/6, 2/3, 1/6, 0}
    };
 public:
    BSplineCurve(const std::vector<Coordinate>& coordinates, utils::Color c);
    void draw();
};

#endif /* BSPLINE_CURVE_H */
