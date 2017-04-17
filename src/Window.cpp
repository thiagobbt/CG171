#include <cmath>
#include "Window.h"
#include "DrawingManager.h"
#include "utils.h"
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
}

void Window::move(double x, double y, double z) {
    auto m = utils::Transformation2D::rotation_matrix(-angle);
    m = m * utils::Transformation2D::translation_matrix(x, y);
    m = m * utils::Transformation2D::rotation_matrix(angle);

    start_point = (utils::Matrix(start_point) * m).to_coord();
    end_point = (utils::Matrix(end_point) * m).to_coord();
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
}

double Window::get_current_zoom() {
    return current_zoom;
}

void Window::rotate(double theta) {
    angle = std::fmod(angle + theta, 360);
}

Coordinate Window::to_viewport(const Coordinate& coord) {
    double width  = viewport.second.get_x() - viewport.first.get_x();
    double height = viewport.second.get_y() - viewport.first.get_y();
    double x = (coord.get_x() + 1) / 2 * width + viewport.first.get_x();
    double y = (1 - (coord.get_y() + 1)/ 2) * height + viewport.first.get_y();

    return Coordinate(x, y);
}

utils::Matrix Window::normalizerMatrix() {
    Coordinate center = (start_point + end_point) / 2.0;
    double width = std::abs(end_point.get_x() - start_point.get_x());
    double height = std::abs(end_point.get_y() - start_point.get_y());

    utils::Matrix normalizer = utils::Transformation2D::translation_matrix(-center.get_x(), -center.get_y());
    normalizer = normalizer * utils::Transformation2D::rotation_matrix(-angle);
    normalizer = normalizer * utils::Transformation2D::scaling_matrix(2 / width, 2 / height);
    return normalizer;
}

void Window::print_coords(std::ostream& out) {
    out << start_point << std::endl;
    out << end_point << std::endl;
}

void Window::set_coords(Coordinate& a, Coordinate& b) {
    start_point = a;
    end_point = b;
}

std::pair<Coordinate, Coordinate> Window::get_viewport_coords() {
    return viewport;
}

bool isPointDrawable(Coordinate& coord) {
    if (coord.get_x() < -1 || coord.get_x() > 1 ||
        coord.get_y() < -1 || coord.get_y() > 1) {
        return false;
    }
    return true;
}

void Window::clipPoint(std::vector<Coordinate>& coords) {
    if (!isPointDrawable(coords[0])) {
        coords.clear();
    }
}

int Window::get_region_code(Coordinate& coord) {
    int result = 0;

    result |= (coord.get_y() > 1);
    result |= (coord.get_y() < -1) << 1;
    result |= (coord.get_x() > 1) << 2;
    result |= (coord.get_x() < -1) << 3;

    return result;
}

void Window::clipCS(std::vector<Coordinate>& coords) {
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

void Window::clipLB(std::vector<Coordinate>& coords) {
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

void Window::clipLine(std::vector<Coordinate>& coords) {
    if (line_clipping_algorithm) {
        clipCS(coords);
    } else {
        clipLB(coords);
    }
}

Coordinate lineIntersection(std::pair<Coordinate, Coordinate> a, std::pair<Coordinate, Coordinate> b) {
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

void clampPoint(Coordinate& c) {
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

void Window::clipPolygon(std::vector<Coordinate>& coords) {
    std::vector<Coordinate> output;
    Coordinate s = coords.back();

    bool addedPoints = false;

    for (size_t i = 0; i < coords.size(); i++) {
        std::vector<Coordinate> currentLine = {s, coords[i]};
        std::vector<Coordinate> realLine = {s, coords[i]};
        Coordinate middlePoint;
        middlePoint[0] = (currentLine[0][0] + currentLine[1][0]);
        middlePoint[1] = (currentLine[0][1] + currentLine[1][1]);

        clipLine(currentLine);

        bool clipped = false;

        if (currentLine[0] != realLine[0] || currentLine[1] != realLine[1])
            clipped = true;

        if (currentLine.size() > 1) {
            if (clipped || !addedPoints || output.empty() || currentLine[0] != output.back()) {
                output.push_back(currentLine[0]);
                clipped = false;
            }
            output.push_back(currentLine[1]);
            clampPoint(realLine[1]);
            output.push_back(realLine[1]);
            addedPoints = true;
        } else {
            Coordinate clipPoint(coords[i]);
            clampPoint(clipPoint);
            clampPoint(middlePoint);
            output.push_back(middlePoint);
            output.push_back(clipPoint);


            addedPoints = false;
        }

        s = coords[i];
    }

    coords = output;
}

void Window::set_clipping_cs() {
    line_clipping_algorithm = true;
}

void Window::set_clipping_lb() {
    line_clipping_algorithm = false;
}

