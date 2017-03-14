/* copyright vfreitas & thiagobbt */

#ifndef WINDOW_H
#define WINDOW_H

#include "Object.h"

class World {
 private:
    Coordinate& starting_point;
    double size;

 public:
    World(const World&);
    World(const Coordinate&, double);
    void move(double, double, double);
    void zoom(double);

};

#endif /* WINDOW_H */