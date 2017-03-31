#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <vector>
#include "utils.h"
#include "Coordinate.h"
#include "Drawable.h"

class Object {
 protected:
    Drawable* drawable_obj;
    std::vector<Coordinate> *world_loc;
    std::vector<Coordinate> *win_loc;

 public:
    ~Object();
    virtual void draw() = 0;
    void transform(utils::Matrix&);
    Coordinate center();
    void update();
};

#endif /* _OBJECT_H_ */
