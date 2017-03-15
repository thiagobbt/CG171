/* copyright vfreitas & thiagobbt */

#ifndef WINDOW_H
#define WINDOW_H

#include "Object.h"
#include "World"
#include "Coordinate.h"

class Window {
 private:
    Coordinate starting_point;
    World world;
    double size;

 public:
    Window(const Coordinate&, double);
    void move(double, double, double);
    void zoom(double);

};

#endif /* WINDOW_H */