#include "Window.h"
#include "DrawingManager.h"
#include "utils.h"
#include <cmath>

Window& Window::instance() {
    static Window instance;
    return instance;
}

Window::Window() {
    start_point = Coordinate(0,0);
    end_point = Coordinate(400,400);
    viewport = {Coordinate(0,0), Coordinate(400, 400)};
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

void Window::rotate(double theta) {
    std::cout << "angle " << angle << " => ";
    angle = std::fmod(angle + theta, 360);
    std::cout << angle << std::endl;
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
