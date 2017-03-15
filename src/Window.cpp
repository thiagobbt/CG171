#include "Window.h"

Window::Window() {
	starting_point = Coordinate(0,0);
	end_point = Coordinate(400,400);
}

Window::Window(const Coordinate& low, const Coordinate& up) 
	: starting_point(low), end_point(up) {
}

void Window::move(double x, double y, double z) {
	starting_point.sum_coords(x, y, z);
	end_point.sum_coords(x, y, z);
}

void Window::zoom(double zoom) {
	double start_x = starting_point.get_x();
	double end_x = end_point.get_x();
	double width = end_x - start_x;
	double start_y = starting_point.get_y();
	double end_y = end_point.get_y();
	double height = end_y - start_y;
	double center_x = (start_x + end_x)/2;
	double center_y = (start_y + end_y)/2;

	if (zoom > 0) {
		double new_width = width/zoom;
		double new_height = height/zoom;
		double new_start_x = center_x - new_width;
		double new_end_x = center_x + new_width;
		double new_start_y = center_y - new_height;
		double new_end_y = center_y + new_height;
		starting_point = Coordinate(new_start_x, new_start_y);
		end_point = Coordinate(new_end_x, new_end_y);
	} else {
		double new_width = width*zoom;
		double new_height = height*zoom;
		double new_start_x = center_x - new_width;
		double new_end_x = center_x + new_width;
		double new_start_y = center_y - new_height;
		double new_end_y = center_y + new_height;
		starting_point = Coordinate(new_start_x, new_start_y);
		end_point = Coordinate(new_end_x, new_end_y);
	}
}

Coordinate Window::to_viewport(Coordinate& coord) {
	// double x = (coord.get_x() - start_point.get_x())
 //               / (end_point.get_x() - start_point.get_x())
 //               * ((*viewport.second).get_x() - (*viewport.first).get_x())
 //               + (*viewport.first).get_x();
 //    double y = (1 - (coord.get_y() - start_point.get_y())
 //               / (end_point.get_y() - start_point.get_y()))
 //               * ((*viewport.second).get_y() - (*viewport.first).get_y())
 //               + (*viewport.first).get_y();
	double x = 0;
	double y = 0;
    return Coordinate(x, y);
}