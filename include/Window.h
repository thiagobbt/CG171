/* copyright vfreitas & thiagobbt */

#ifndef WINDOW_H
#define WINDOW_H

#include "Object.h"

class World {
 private:
    Coordinate& starting_point;
    Coordinate& end_point;

 public:
    World(const World&);
    World(const Coordinate&, double);
    void move(double, double, double);
    void zoom(double);
    Coordinate toViewport(Coordinate&, Coordinate&, Coordinate&);
};

#endif /* WINDOW_H */