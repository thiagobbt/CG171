#ifndef LINE_H
#define LINE_H

#include <vector>
#include "Object.h"
#include "utils.h"

class Line : public Object {
 private:
    utils::Color color;
 public:
    Line(const std::vector<Coordinate>&, utils::Color);
    void draw();
};

#endif /* LINE_H */