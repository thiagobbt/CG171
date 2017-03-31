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

	start_point.sum_coords(m(0, 0), m(0, 1), m(0, 2));
	end_point.sum_coords(m(0, 0), m(0, 1), m(0, 2));
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

Coordinate Window::to_viewport(const Coordinate& coord) {
	// double x = (coord.get_x() - start_point.get_x())
 //               / (end_point.get_x() - start_point.get_x())
 //               * ((viewport.second).get_x() - (viewport.first).get_x())
 //               + (viewport.first).get_x();
 //    double y = (1 - (coord.get_y() - start_point.get_y())
 //               / (end_point.get_y() - start_point.get_y()))
 //               * ((viewport.second).get_y() - (viewport.first).get_y())
 //               + (viewport.first).get_y();

    double x = (coord.get_x() - -1)
               / (1 - -1)
               * ((viewport.second).get_x() - (viewport.first).get_x())
               + (viewport.first).get_x();
    double y = (1 - (coord.get_y() - -1)
               / (1 - -1))
               * ((viewport.second).get_y() - (viewport.first).get_y())
               + (viewport.first).get_y();

 //    utils::Matrix a(1,3);
 //    a(0, 0) = x;
 //    a(0, 1) = y;
 //    a(0, 2) = 1;

 //    Coordinate center(200, 200);

 //    auto translate = utils::Transformation2D::translation_matrix(-center.get_x(), -center.get_y());
 //    auto rotate = utils::Transformation2D::rotation_matrix(angle);
 //    auto translate_back = utils::Transformation2D::translation_matrix(center.get_x(), center.get_y());

	// auto result = a * translate * rotate * translate_back;

	// return Coordinate(result(0, 0), result(0, 1));

    return Coordinate(x, y);
}

// Coordinate Window::to_window(const Coordinate& world_coord) {
// 	double width = end_point.get_x() - start_point.get_x();
// 	double height = end_point.get_y() - start_point.get_y();

// 	double new_x = (world_coord.get_x() / (width / 2)) - 1;
// 	double new_y = (world_coord.get_y() / (height / 2)) - 1;

// 	return Coordinate(new_x, new_y);
// }

utils::Matrix Window::normalizerMatrix() {
    Coordinate center = (start_point + end_point)/-2.0;
    utils::Matrix normalizer = utils::Transformation2D::translation_matrix(center.get_x(), center.get_y());
    normalizer = normalizer * utils::Transformation2D::rotation_matrix(-angle);
    std::array<double, 2> s = {2/(end_point.get_x() - start_point.get_x()), 2/(end_point.get_y() - start_point.get_y())};
    normalizer = normalizer * utils::Transformation2D::scaling_matrix(s[0], s[1]);
    return normalizer;
}
