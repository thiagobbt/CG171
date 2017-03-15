/* copyright vfreitas & thiagobbt */

#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <vector>
#include <string>
#include "World.h"

using std::string = string;

class Controller {
 private:
 	World& world;

 public:
  	Controller();
 	bool add_point(const string&, double, double);
 	bool add_line(const string&, double, double, double, double);
 	bool add_polygon(string, const std::vector<double>&);
 	
 	bool delete_obj(const string&);
 	
 	void zoom_in(double);
 	void zoom_out(double);
 	void pan_x(double);
 	void pan_y(double);
 	//pan_z(double);
};

#endif /* _CONTROLLER_H_ */