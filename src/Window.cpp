#include "Window.h"
#include "DrawingManager.h"

#define DEBUG(X) std::cout << #X << ": " << X << std::endl;

Window::Window() {
	starting_point = Coordinate(0,0);
	end_point = Coordinate(400,400);
	viewport = {Coordinate(0,0), Coordinate(400, 400)};
	DrawingManager::instance().set_window(this);
}

Window::Window(const Coordinate& low, const Coordinate& up) 
	: starting_point(low), end_point(up) {
	viewport = {Coordinate(0,0), Coordinate(400, 400)};
	DrawingManager::instance().set_window(this);
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

	DEBUG(start_x);
	DEBUG(end_x);
	DEBUG(start_y);
	DEBUG(end_y);
	DEBUG(width);
	DEBUG(height);
	DEBUG(center_x);
	DEBUG(center_y);

	// if (zoom > 1) {
		double new_width = width/zoom;
		double new_height = height/zoom;
		double new_start_x = center_x - new_width;
		double new_end_x = center_x + new_width;
		double new_start_y = center_y - new_height;
		double new_end_y = center_y + new_height;

		DEBUG(new_width);
		DEBUG(new_height);
		DEBUG(new_start_x);
		DEBUG(new_start_y);
		DEBUG(new_end_x);
		DEBUG(new_end_y);

		starting_point = Coordinate(new_start_x, new_start_y);
		end_point = Coordinate(new_end_x, new_end_y);
	// } else {
	// 	double new_width = width*zoom;
	// 	double new_height = height*zoom;
	// 	double new_start_x = center_x - new_width;
	// 	double new_end_x = center_x + new_width;
	// 	double new_start_y = center_y - new_height;
	// 	double new_end_y = center_y + new_height;
	// 	starting_point = Coordinate(new_start_x, new_start_y);
	// 	end_point = Coordinate(new_end_x, new_end_y);
	// }
}

Coordinate Window::to_viewport(Coordinate& coord) {
	double x = (coord.get_x() - starting_point.get_x())
               / (end_point.get_x() - starting_point.get_x())
               * ((viewport.second).get_x() - (viewport.first).get_x())
               + (viewport.first).get_x();
    double y = (1 - (coord.get_y() - starting_point.get_y())
               / (end_point.get_y() - starting_point.get_y()))
               * ((viewport.second).get_y() - (viewport.first).get_y())
               + (viewport.first).get_y();

    return Coordinate(x, y);
}