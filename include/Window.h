#ifndef WINDOW_H
#define WINDOW_H

#include "Object.h"
#include "World.h"
#include "utils.h"

class Window {
 private:
    Coordinate start_point;
    Coordinate end_point;
    std::pair<Coordinate, Coordinate> viewport;
    double default_width, default_height;
    double current_zoom = 1;
    double zoom_factor = 0.1;
    double angle = 0;

 protected:
    Window();

 public:
    static Window& instance();
    void move(double, double, double);
    void zoom(double);
    void rotate(double);
    Coordinate to_viewport(const Coordinate&);
    Coordinate to_window(const Coordinate&);
    utils::Matrix normalizerMatrix();
};

#endif /* WINDOW_H */