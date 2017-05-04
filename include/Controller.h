#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include <string>
#include "utils.h"

namespace cb {
    void add_to_obj_list(std::string name, std::string type);
}

using std::string;

class Controller {
 public:
    Controller() {}
    bool add_point(const string&, const Coordinate&, utils::Color);
    bool add_line(const string&, const Coordinate&, const Coordinate&, utils::Color);
    bool add_polygon(const string&, const std::vector<Coordinate>&, utils::Color, bool);
    bool add_bezier_curve(const string&, const std::vector<Coordinate>&, utils::Color);
    bool add_bspline_curve(const string&, const std::vector<Coordinate>&, utils::Color);
    
    void delete_obj(const string&);
    void clear_world();
    
    void zoom_in(double);
    void zoom_out(double);
    void pan_x(double);
    void pan_y(double);
    void pan_z(double);
    void rotate(double, double, double);

    void move_obj(const string&, double, double, double);
    void rotate_obj(const string&, double, double, double, Coordinate, bool);
    void scale_obj(const string&, double, double, double);

    void export_obj(std::ostream&) const;
    void import_obj(std::istream&);

    void set_clipping_cs();
    void set_clipping_lb();
};

#endif /* CONTROLLER_H */
