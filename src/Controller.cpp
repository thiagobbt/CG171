#include "Controller.h"
#include "BSplineCurve.h"
#include "BezierCurve.h"
#include "Coordinate.h"
#include "Line.h"
#include "Point.h"
#include "Polygon.h"
#include "World.h"
#include "utils.h"
#include <cassert>
#include <cmath>
#include <limits>
#include <string>

bool Controller::add_point(const string& id, const Coordinate& coord, utils::Color c) {
    bool res = World::instance().add_obj(id, new Point({coord}, c));
    if (res) World::instance().update_obj(id);
    return res;
}

bool Controller::add_line(const string& id, const Coordinate& c1, const Coordinate& c2, utils::Color c) {
    bool res = World::instance().add_obj(id, new Line({c1,c2},c));
    if (res) World::instance().update_obj(id);
    return res;
}

bool Controller::add_polygon(const string &id, const std::vector<Coordinate>& coords, utils::Color c, bool fill) {
    bool res = World::instance().add_obj(id, new Polygon(coords, c, fill));
    if (res) World::instance().update_obj(id);
    return res;
}

bool Controller::add_bezier_curve(const string& id, const std::vector<Coordinate>& coords, utils::Color c) {
    bool res = World::instance().add_obj(id, new BezierCurve(coords, c));
    if (res) World::instance().update_obj(id);
    return res;
}

bool Controller::add_bspline_curve(const string& id, const std::vector<Coordinate>& coords, utils::Color c) {
    bool res = World::instance().add_obj(id, new BSplineCurve(coords, c));
    if (res) World::instance().update_obj(id);
    return res;
}

void Controller::delete_obj(const string& key) {
    World::instance().delete_obj(key);
}

void Controller::clear_world() {
    World::instance().clear();
}

void Controller::zoom_in(double zoom) {
    Window::instance().zoom(zoom);
    World::instance().update_all();
}


void Controller::zoom_out(double zoom) {
    Window::instance().zoom(1/zoom);
    World::instance().update_all();
}

void Controller::pan_x(double x) {
    Window::instance().move(x,0,0);
    World::instance().update_all();
}

void Controller::pan_y(double y) {
    Window::instance().move(0,y,0);
    World::instance().update_all();
}

void Controller::rotate(double theta) {
    Window::instance().rotate(theta);
    World::instance().update_all();
}

void Controller::move_obj(const string& id, double dx, double dy) {
    auto a = utils::Transformation2D::translation_matrix(dx, dy);
    World::instance().move_obj(id, a);
}

void Controller::rotate_obj(const string& id, double theta, double x, double y, bool use_cord) {
    auto a = utils::Transformation2D::rotation_matrix(theta);
    Coordinate loc(x, y);
    World::instance().rotate_obj(id, a, loc, use_cord);
} 

void Controller::scale_obj(const string& id, double sx, double sy) {
    auto a = utils::Transformation2D::scaling_matrix(sx, sy);
    World::instance().scale_obj(id, a);
    World::instance().update_obj(id);
}

void Controller::export_obj(std::ostream &out) {
    auto display_file = World::instance().get_display_file();

    int n_coords = 0;

    for (auto obj : display_file) {
        n_coords += obj.second->num_coords();
        out << "# " << obj.first << std::endl;
        out << *(obj.second);
    }

    out << "# window" << std::endl;
    Window::instance().print_coords(out);

    // out << "mtllib materials.mtl" << std::endl;
    out << "o window" << std::endl;
    out << "w " << n_coords + 1 << " " << n_coords + 2 << std::endl;

    int coord_counter = 1;

    for (auto obj : display_file) {
        int obj_n_coords = obj.second->num_coords();
        out << "o " << obj.first << std::endl;
        out << (obj_n_coords == 1? "p" : "l");

        for (int i = coord_counter; i < coord_counter + obj_n_coords; i++) {
            out << " " << i;
        }

        if (obj_n_coords > 2) out << " " << coord_counter;

        coord_counter += obj_n_coords;

        out << std::endl;
    }
}

void Controller::import_obj(std::istream &in) {
    std::vector<Coordinate> coords;
    std::vector<Coordinate> polygon_coords;
    std::string object_name;

    char line_type;
    while (in >> line_type) {
        switch (line_type) {
            case 'w':
                int start_point, end_point;
                in >> start_point >> end_point;
                in.ignore(std::numeric_limits<std::streamsize>::max(), in.widen('\n'));
                Window::instance().set_coords(coords[start_point-1], coords[end_point-1]);
                break;
            case 'o':
                in >> object_name;
                in.ignore(std::numeric_limits<std::streamsize>::max(), in.widen('\n'));
                break;
            case 'p':
                int a;
                in >> a;
                in.ignore(std::numeric_limits<std::streamsize>::max(), in.widen('\n'));
                add_point(object_name, coords[a-1], utils::Color{0, 1, 0});
                cb::add_to_obj_list(object_name, "Point");
                break;
            case 'l':
                int tmp_polygon_index;
                polygon_coords.clear();
                while ((in.peek() != '\n') && (in >> tmp_polygon_index)) {
                    polygon_coords.push_back(coords[tmp_polygon_index-1]);
                }
                in.ignore(std::numeric_limits<std::streamsize>::max(), in.widen('\n'));
                if (polygon_coords.size() == 2) {
                    add_line(
                        object_name,
                        polygon_coords[0],
                        polygon_coords[1],
                        utils::Color{0, 1, 0}
                    );
                    cb::add_to_obj_list(object_name, "Line");
                } else {
                    polygon_coords.pop_back();
                    add_polygon(
                        object_name,
                        polygon_coords,
                        utils::Color{0, 1, 0},
                        false
                    );
                    cb::add_to_obj_list(object_name, "Polygon");
                }
                break;
            case 'v':
                double x, y, z;
                in >> x >> y >> z;
                in.ignore(std::numeric_limits<std::streamsize>::max(), in.widen('\n'));
                coords.emplace_back(x, y, z);
                break;
            default:
                in.ignore(std::numeric_limits<std::streamsize>::max(), in.widen('\n'));
                break;
        }
    }
}

void Controller::set_clipping_cs() {
    Window::instance().set_clipping_cs();
}

void Controller::set_clipping_lb() {
    Window::instance().set_clipping_lb();
}
