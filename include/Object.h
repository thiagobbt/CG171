#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "utils.h"
#include "Coordinate.h"
#include "Drawable.h"

class Object {
 protected:
    Drawable* drawable_obj;
    std::vector<Coordinate> world_loc;
    std::vector<Coordinate> win_loc;

 public:
    ~Object();
    virtual void draw() = 0;
    void transform(utils::Matrix&);
    Coordinate center();
    void update();
};

#endif /* OBJECT_H */
