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
    void clipCS(std::vector<Coordinate>&) const;
    void clipLB(std::vector<Coordinate>&) const;
    bool isPointDrawable(const Coordinate&) const;
    int get_region_code(const Coordinate&) const;
    const Coordinate lineIntersection(const std::pair<Coordinate, Coordinate>, const std::pair<Coordinate, Coordinate>) const;
    void clampPoint(Coordinate& c) const;
    bool line_clipping_algorithm = true;
    double current_zoom = 1;

 protected:
    Window();

 public:
    static Window& instance();
    void move(double, double, double);
    void zoom(double);
    double get_current_zoom() const;
    void rotate(double, double, double);
    const Coordinate to_viewport(const Coordinate&) const;
    const Coordinate to_window(const Coordinate&) const;
    const utils::Matrix normalizerMatrix() const;
    void print_coords(std::ostream&) const;
    void set_coords(Coordinate&, Coordinate&);
    const std::pair<Coordinate, Coordinate> get_viewport_coords() const;

    void clipPoint(std::vector<Coordinate>&) const;
    void clipLine(std::vector<Coordinate>&) const;
    void clipPolygon(std::vector<Coordinate>&) const;

    void set_clipping_cs();
    void set_clipping_lb();
};

#endif /* WINDOW_H */
