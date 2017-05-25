#include "Window.h"
#include "DrawingManager.h"
#include "utils.h"
#include <cmath>
#include <cstdint>

Window& Window::instance() {
    static Window instance;
    return instance;
}

Window::Window() {
    start_point = Coordinate(0, 0);
    end_point = Coordinate(400, 400);
    viewport = {Coordinate(10, 10), Coordinate(390, 390)};
    DrawingManager::instance().set_window(this);
    default_width = 400;
    default_height = 400;
    cop = {200, 200, -100};
    vpn = {{200, 200, 0}, {200, 200, 1}};
}

void Window::move(double x, double y, double z) {
    auto m = utils::Transformation3D::rotation_matrix_x(-angle_x);
    m *= utils::Transformation3D::rotation_matrix_y(-angle_y);
    m *= utils::Transformation3D::rotation_matrix_z(-angle_z);
    m *= utils::Transformation3D::translation_matrix(x, y, z);
    m *= utils::Transformation3D::rotation_matrix_x(angle_x);
    m *= utils::Transformation3D::rotation_matrix_y(angle_y);
    m *= utils::Transformation3D::rotation_matrix_z(angle_z);

    start_point = (utils::Matrix(start_point, 4) * m).to_coord();
    end_point = (utils::Matrix(end_point, 4) * m).to_coord();
    cop = (utils::Matrix(cop, 4) * m).to_coord();
    vpn.first = (utils::Matrix(vpn.first, 4) * m).to_coord();
    vpn.second = (utils::Matrix(vpn.second, 4) * m).to_coord();
}

void Window::zoom(double zoom) {
    current_zoom *= zoom;
    double center_x = (start_point.get_x() + end_point.get_x()) / 2;
    double center_y = (start_point.get_y() + end_point.get_y()) / 2;

    double width = (end_point.get_x() - start_point.get_x()) / zoom;
    double height = (end_point.get_y() - start_point.get_y()) / zoom;

    double new_start_x = center_x - width/2;
    double new_start_y = center_y - height/2;
    double new_end_x = center_x + width/2;
    double new_end_y = center_y + height/2;

    start_point = Coordinate(new_start_x, new_start_y);
    end_point = Coordinate(new_end_x, new_end_y);

    // auto midpoint = (start_point + end_point)/2;

    // cop[0] = midpoint[0];
    // vpn.first[0] = midpoint[0];
    // vpn.second[0] = midpoint[0];

    // cop[1] = midpoint[1];
    // vpn.first[1] = midpoint[1];
    // vpn.second[1] = midpoint[1];
}

double Window::get_current_zoom() const {
    return current_zoom;
}

void Window::rotate(double theta_x, double theta_y, double theta_z) {
    angle_x = std::fmod(angle_x + theta_x, 360);
    angle_y = std::fmod(angle_y + theta_y, 360);
    angle_z = std::fmod(angle_z + theta_z, 360);

    // auto rotation = utils::Transformation3D::rotation_matrix_x(theta_x);
    // rotation *= utils::Transformation3D::rotation_matrix_y(theta_y);
    // rotation *= utils::Transformation3D::rotation_matrix_z(theta_z);
    // cop = (utils::Matrix(cop, 4) * rotation).to_coord();
    // vpn.first = (utils::Matrix(vpn.first, 4) * rotation).to_coord();
    // vpn.second = (utils::Matrix(vpn.second, 4) * rotation).to_coord();
}

const Coordinate Window::perspective(const Coordinate& coord) const {
    // return Coordinate(coord[0], coord[1]);
    using utils::Transformation3D::translation_matrix;
    using utils::Transformation3D::rotation_matrix_x;
    using utils::Transformation3D::rotation_matrix_y;
    auto p = coord;
    auto transformation = translation_matrix(-cop[0], -cop[1], -cop[2]);

    Coordinate xAxis(1, 0, 0);
    Coordinate yAxis(0, 1, 0);
    Coordinate vector = vpn.second - vpn.first;
    double tx = acos((xAxis * vector) / vector.norm()) * 180 / M_PI;
    double ty = acos((yAxis * vector) / vector.norm()) * 180 / M_PI;
    transformation *= rotation_matrix_x(90 - tx);
    transformation *= rotation_matrix_y(90 - ty);
    p *= transformation;

    double d = p[2] - cop[2];
    double correctionFactor = p[2] / d;
    p[0] /= correctionFactor;
    p[1] /= correctionFactor;

    p *= translation_matrix(cop[0], cop[1], cop[2]);

    return p;
}

const Coordinate Window::to_viewport(const Coordinate& coord) const {
    if (coord.get_z() > -cop.get_z()) {
        auto tmp = coord;
        tmp[2] = -cop.get_z();
        return tmp;
    }

    double width  = viewport.second.get_x() - viewport.first.get_x();
    double height = viewport.second.get_y() - viewport.first.get_y();
    double x = (coord.get_x() + 1) / 2 * width + viewport.first.get_x();
    double y = (1 - (coord.get_y() + 1)/ 2) * height + viewport.first.get_y();

    return Coordinate(x, y);
}

const utils::Matrix Window::normalizerMatrix() const {
    Coordinate center = (start_point + end_point) / 2.0;
    double width = std::abs(end_point.get_x() - start_point.get_x());
    double height = std::abs(end_point.get_y() - start_point.get_y());
    double depth = std::abs(end_point.get_z() - start_point.get_z());

    utils::Matrix normalizer = utils::Transformation3D::translation_matrix(-center.get_x(), -center.get_y(), -center.get_z());
    normalizer *= utils::Transformation3D::rotation_matrix_x(-angle_x);
    normalizer *= utils::Transformation3D::rotation_matrix_y(-angle_y);
    normalizer *= utils::Transformation3D::rotation_matrix_z(-angle_z);
    normalizer *= utils::Transformation3D::scaling_matrix(2 / width, 2 / height,  2 / depth);
    return normalizer;
}

void Window::print_coords(std::ostream& out) const {
    out << start_point << std::endl;
    out << end_point << std::endl;
}

void Window::set_coords(Coordinate& a, Coordinate& b) {
    start_point = a;
    end_point = b;
}

const std::pair<Coordinate, Coordinate> Window::get_viewport_coords() const {
    return viewport;
}

bool Window::isPointDrawable(const Coordinate& coord) const {
    return !(coord.get_x() < -1 || coord.get_x() > 1 || coord.get_y() < -1 || coord.get_y() > 1);
}

void Window::clipPoint(std::vector<Coordinate>& coords) const {
    if (!isPointDrawable(coords[0])) {
        coords.clear();
    }
}

int Window::get_region_code(const Coordinate& coord) const {
    int result = 0;

    result |= static_cast<int>(coord.get_y() > 1);
    result |= static_cast<int>(coord.get_y() < -1) << 1;
    result |= static_cast<int>(coord.get_x() > 1) << 2;
    result |= static_cast<int>(coord.get_x() < -1) << 3;

    return result;
}

void Window::clipCS(std::vector<Coordinate>& coords) const {
    auto rc0 = get_region_code(coords[0]);
    auto rc1 = get_region_code(coords[1]);

    if (rc0 == 0 && rc1 == 0) {
        return;
    }

    if ((rc0 & rc1) != 0) {
        coords.clear();
        return;
    }

    int rc = (rc0 == 0) ? rc1 : rc0;

    double m = (coords[1].get_y() - coords[0].get_y()) / (coords[1].get_x() - coords[0].get_x());

    double x, y;

    if ((rc & 1) != 0) {
        x = coords[0].get_x() + (1 - coords[0].get_y()) / m;
        y = 1;
    } else if ((rc & 2) != 0) {
        x = coords[0].get_x() + (-1 - coords[0].get_y()) / m;
        y = -1;
    } else if ((rc & 4) != 0) {
        x = 1;
        y = coords[0].get_y() + m * (1 - coords[0].get_x());
    } else {
        x = -1;
        y = coords[0].get_y() + m * (-1 - coords[0].get_x());
    }

    if (rc == rc0) {
        coords[0] = Coordinate(x, y);
    } else {
        coords[1] = Coordinate(x, y);
    }

    clipCS(coords);
}

void Window::clipLB(std::vector<Coordinate>& coords) const {
    double dx = coords[1].get_x() - coords[0].get_x();
    double dy = coords[1].get_y() - coords[0].get_y();

    std::vector<double> p;
    p.push_back(-dx);
    p.push_back(dx);
    p.push_back(-dy);
    p.push_back(dy);

    std::vector<double> q;
    q.push_back(coords[0].get_x() - -1);
    q.push_back(1 - coords[0].get_x());
    q.push_back(coords[0].get_y() - -1);
    q.push_back(1 - coords[0].get_y());

    std::vector<double> r;
    for (int i = 0; i < 4; i++) {
        r.push_back(q[i]/p[i]);
    }

    double zetta1 = 0;
    double zetta2 = 1;

    for (int i = 0; i < 4; i++) {
        if (p[i] < 0) {
            zetta1 = std::max(zetta1, r[i]);
        } else {
            zetta2 = std::min(zetta2, r[i]);
        }
    }

    if (zetta1 >= zetta2) {
        coords.clear();
        return;
    }

    if (zetta2 != 0 && zetta2 != 1) {
        coords[1] = Coordinate(coords[0].get_x() + zetta2 * dx, coords[0].get_y() + zetta2 * dy);
    }

    if (zetta1 != 0 && zetta1 != 1) {
        coords[0] = Coordinate(coords[0].get_x() + zetta1 * dx, coords[0].get_y() + zetta1 * dy);
    }
}

void Window::clipLine(std::vector<Coordinate>& coords) const {
    if (line_clipping_algorithm) {
        clipCS(coords);
    } else {
        clipLB(coords);
    }
}

const Coordinate Window::lineIntersection(const std::pair<Coordinate, Coordinate> a, const std::pair<Coordinate, Coordinate> b) const {
    Coordinate result(0, 0);
    auto& p1 = a.first;
    auto& p2 = a.second;
    auto& p3 = b.first;
    auto& p4 = b.second;

    double d = (p1[0] - p2[0])*(p3[1] - p4[1]) - (p1[1] - p2[1])*(p3[0] - p4[0]);

    if (d == 0) return result;

    double common1 = (p1[0]*p2[1] - p1[1]*p2[0]);
    double common2 = (p3[0]*p4[1] - p3[1]*p4[0]);

    result[0] = ((common1*(p3[0]-p4[0])) - ((p1[0]-p2[0])*common2)) / d;
    result[1] = ((common1*(p3[1]-p4[1])) - ((p1[1]-p2[1])*common2)) / d;

    return result;
}

void Window::clampPoint(Coordinate& c) const {
    if (c[0] < -1) {
        c[0] = -1;
    }

    if (c[0] > 1) {
        c[0] = 1;
    }

    if (c[1] < -1) {
        c[1] = -1;
    }

    if (c[1] > 1) {
        c[1] = 1;
    }
}

void Window::clipPolygon(std::vector<Coordinate>& coords) const {
    std::vector<Coordinate> output;
    Coordinate s = coords.back();

    bool addedPoints = false;

    for (auto currentPoint : coords) {
        std::vector<Coordinate> currentLine = {s, currentPoint};
        std::vector<Coordinate> realLine = {s, currentPoint};
        Coordinate middlePoint;
        middlePoint[0] = (currentLine[0][0] + currentLine[1][0]);
        middlePoint[1] = (currentLine[0][1] + currentLine[1][1]);

        clipCS(currentLine);

        bool clipped = false;

        if (currentLine[0] != realLine[0] || currentLine[1] != realLine[1])
            clipped = true;

        if (currentLine.size() > 1) {
            if (clipped || !addedPoints || output.empty() || currentLine[0] != output.back()) {
                output.push_back(currentLine[0]);
            }
            output.push_back(currentLine[1]);
            clampPoint(realLine[1]);
            output.push_back(realLine[1]);
            addedPoints = true;
        } else {
            Coordinate clipPoint(currentPoint);
            clampPoint(clipPoint);
            clampPoint(middlePoint);
            output.push_back(middlePoint);
            output.push_back(clipPoint);


            addedPoints = false;
        }

        s = currentPoint;
    }

    coords = output;
}

void Window::set_clipping_cs() {
    line_clipping_algorithm = true;
}

void Window::set_clipping_lb() {
    line_clipping_algorithm = false;
}

