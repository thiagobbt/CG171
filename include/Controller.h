/* copyright vfreitas & thiagobbt */

#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <vector>
#include <string>
#include "DrawingManager.h"
#include "Window.h"

using std::string;

class Controller {
 private:
 	Window win;

 public:
	Controller() {}
	bool add_point(const string&, double, double, utils::Color);
	bool add_line(const string&, double, double, double, double, utils::Color);
	bool add_polygon(const string&, const std::vector<double>&, utils::Color, bool);
	
	void delete_obj(const string&);
	void clear_world();
	
	void zoom_in(double);
	void zoom_out(double);
	void pan_x(double);
	void pan_y(double);
	//pan_z(double);

	void move_obj(const string&, double, double);
	void rotate_obj(const string&, double, double, double, bool);
	void scale_obj(const string&, double, double);
};

#endif /* _CONTROLLER_H_ */