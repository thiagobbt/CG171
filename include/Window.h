#ifndef WINDOW_H
#define WINDOW_H

#include "utils.h"

class Window {
 private:
    Coordinate start_point;
    Coordinate end_point;
    std::pair<Coordinate, Coordinate> viewport;
    double default_width, default_height;
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
    void print_coords(std::ostream&);
    void set_coords(Coordinate&, Coordinate&);
};

#endif /* WINDOW_H */
