#ifndef BEZIER_CURVE_H
#define BEZIER_CURVE_H

#include <vector>
#include "Curve.h"

class BezierCurve : public Curve {
 private:
    std::vector<Coordinate> original_loc;
    void update_coords();
    const utils::Matrix mb = {
        {-1, 3, -3, 1},
        {3, -6, 3, 0},
        {-3, 3, 0, 0},
        {1, 0, 0, 0}
    };
 public:
    BezierCurve(const std::vector<Coordinate>& coordinates, utils::Color c);
    void draw();
};

#endif /* BEZIER_CURVE_H */
