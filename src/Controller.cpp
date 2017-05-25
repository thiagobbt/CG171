#include "Controller.h"
#include "BSplineCurve.h"
#include "BezierCurve.h"
#include "Coordinate.h"
#include "FileManager.h"
#include "Line.h"
#include "Point.h"
#include "Polygon.h"
#include "SurfaceBezier.h"
#include "World.h"
#include "utils.h"
#include <cassert>
#include <cmath>
#include <limits>
#include <string>

bool Controller::add_point(const string& id, const Coordinate& coord, utils::Color c) {
    bool res = World::instance().add_obj(id, new Point({coord}, c));
    if (res) {
        World::instance().update_obj(id);
        cb::add_to_obj_list(id, "Point");
    }
    return res;
}

bool Controller::add_line(const string& id, const Coordinate& c1, const Coordinate& c2, utils::Color c) {
    bool res = World::instance().add_obj(id, new Line({c1,c2},c));
    if (res) {
        World::instance().update_obj(id);
        cb::add_to_obj_list(id, "Line");
    }
    return res;
}

bool Controller::add_polygon(const string &id, const std::vector<Coordinate>& coords, utils::Color c, bool fill) {
    bool res = World::instance().add_obj(id, new Polygon(coords, c, fill));
    if (res) {
        World::instance().update_obj(id);
        cb::add_to_obj_list(id, "Polygon");
    }
    return res;
}

bool Controller::add_bezier_curve(const string& id, const std::vector<Coordinate>& coords, utils::Color c) {
    bool res = World::instance().add_obj(id, new BezierCurve(coords, c));
    if (res) {
        World::instance().update_obj(id);
        cb::add_to_obj_list(id, "Bezier");
    }
    return res;
}

bool Controller::add_bspline_curve(const string& id, const std::vector<Coordinate>& coords, utils::Color c) {
    bool res = World::instance().add_obj(id, new BSplineCurve(coords, c));
    if (res) {
        World::instance().update_obj(id);
        cb::add_to_obj_list(id, "B-Spline");
    }
    return res;
}

bool Controller::add_bezier_surface(const string& id, const std::vector<Coordinate>& coords, utils::Color c) {
    bool res = World::instance().add_obj(id, new SurfaceBezier(coords, c));
    if (res) {
        World::instance().update_obj(id);
        cb::add_to_obj_list(id, "BezierSurface");
    }
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
    Window::instance().move(x, 0, 0);
    World::instance().update_all();
}

void Controller::pan_y(double y) {
    Window::instance().move(0, y, 0);
    World::instance().update_all();
}

void Controller::pan_z(double z) {
    Window::instance().move(0, 0, z);
    World::instance().update_all();
}

void Controller::rotate(double theta_x, double theta_y, double theta_z) {
    Window::instance().rotate(theta_x, theta_y, theta_z);
    World::instance().update_all();
}

void Controller::move_obj(const string& id, double dx, double dy, double dz = 0) {
    auto a = utils::Transformation3D::translation_matrix(dx, dy, dz);
    World::instance().move_obj(id, a);
}

void Controller::rotate_obj(const string& id, double theta_x, double theta_y, double theta_z, Coordinate loc, bool use_cord) {
    auto a = utils::Transformation3D::rotation_matrix_x(theta_x);
    a = a * utils::Transformation3D::rotation_matrix_y(theta_y);
    a = a * utils::Transformation3D::rotation_matrix_z(theta_z);
    World::instance().rotate_obj(id, a, loc, use_cord);
} 

void Controller::scale_obj(const string& id, double sx, double sy, double sz) {
    auto a = utils::Transformation3D::scaling_matrix(sx, sy, sz);
    World::instance().scale_obj(id, a);
    World::instance().update_obj(id);
}

void Controller::export_obj(const std::string& filename) const {
    auto display_file = World::instance().get_display_file();
    FileManager::toObj(filename, display_file);
}

void Controller::import_obj(const std::string& filename) {
    FileManager::fromObj(filename);
}

void Controller::set_clipping_cs() {
    Window::instance().set_clipping_cs();
}

void Controller::set_clipping_lb() {
    Window::instance().set_clipping_lb();
}
