/* copyright vfreitas & thiagobbt */

#include "Object.h"
#include "utils.h"
#include <iostream>


// THIS HAVE TO BE TESTED: use of not of reference on P
void Object::transform(utils::Matrix& b) {
	std::cout << "obj::transform" << std::endl;
	for (auto& p : location) {
		std::cout << "p.x: " << p.get_x();

		utils::Matrix a(1,3);

		a(0, 0) = p.get_x();
		a(0, 1) = p.get_y();
		a(0, 2) = 1;

		utils::Matrix result = a * b;
		
		Coordinate c(result(0,0), result(0,1));

		p = c;
		std::cout << " => " << p.get_x() << std::endl;
	}
}

Coordinate Object::center() {
	double xc = 0;
	double yc = 0;

	for (auto coord : location) {
		xc += coord.get_x();
		yc += coord.get_y();
	}

	xc /= location.size();
	yc /= location.size();

	return Coordinate(xc, yc);
}