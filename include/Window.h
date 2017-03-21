/* copyright vfreitas & thiagobbt */

#ifndef WINDOW_H
#define WINDOW_H

#include "Object.h"
#include "World.h"


class Window {
 private:
    Coordinate starting_point;
    Coordinate end_point;
    std::pair<Coordinate, Coordinate> viewport;
    double default_width, default_height;
    double current_zoom = 1;
    double zoom_factor = 0.1;

 public:
 	Window();
    Window(const Coordinate&, const Coordinate&);
    void move(double, double, double); // x,y,z
    void zoom(double);
    Coordinate to_viewport(Coordinate&);
};

#endif /* WINDOW_H */