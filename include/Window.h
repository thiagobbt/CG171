#ifndef WINDOW_H
#define WINDOW_H

#include "utils.h"

class Window {
 private:
    Coordinate start_point;
    Coordinate end_point;
    std::pair<Coordinate, Coordinate> viewport;
    double default_width, default_height;
    double angle_x = 0;
    double angle_y = 0;
    double angle_z = 0;
    void clipCS(std::vector<Coordinate>&);
    void clipLB(std::vector<Coordinate>&);
    int get_region_code(Coordinate&);
    bool line_clipping_algorithm = true;
    double current_zoom = 1;

 protected:
    Window();

 public:
    static Window& instance();
    void move(double, double, double);
    void zoom(double);
    double get_current_zoom();
    void rotate(double, double, double);
    Coordinate to_viewport(const Coordinate&);
    Coordinate to_window(const Coordinate&);
    utils::Matrix normalizerMatrix();
    void print_coords(std::ostream&);
    void set_coords(Coordinate&, Coordinate&);
    std::pair<Coordinate, Coordinate> get_viewport_coords();

    void clipPoint(std::vector<Coordinate>&);
    void clipLine(std::vector<Coordinate>&);
    void clipPolygon(std::vector<Coordinate>&);

    void set_clipping_cs();
    void set_clipping_lb();
};

#endif /* WINDOW_H */
