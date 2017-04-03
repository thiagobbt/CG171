#ifndef OBJECT_H
#define OBJECT_H

#include <memory>
#include <vector>
#include "utils.h"
#include "Coordinate.h"
#include "Drawable.h"

class Object {
 protected:
    std::unique_ptr<Drawable> drawable_obj;
    std::vector<Coordinate> world_loc;
    std::vector<Coordinate> win_loc;

 public:
    virtual void draw() = 0;
    void transform(utils::Matrix&);
    const Coordinate center() const;
    void update();
    const int num_coords() const;
    friend std::ostream& operator<<(std::ostream& out, const Object& w);
};

#endif /* OBJECT_H */
