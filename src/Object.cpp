/* copyright vfreitas & thiagobbt */

#include "Object.h"
#include "utils.h"
#include <iostream>


// THIS HAVE TO BE TESTED: use of not of reference on P
void Object::transform(utils::Matrix& b) {
	std::cout << "obj::transform" << std::endl;
	for (auto p : location) {
		std::cout << p.get_x() << std::endl;

		utils::Matrix *a = new utils::Matrix(1,3);
		a->fill(0);

		(*a)(0, 0) = p.get_x();
		(*a)(0, 1) = p.get_y();
		(*a)(0, 2) = 1;

		utils::Matrix *banana = new utils::Matrix((*a) * b);
		
		std::cout << "darkness 2" << std::endl;
		Coordinate c((*banana)(0,0), (*banana)(0,1));
		std::cout << "constructed coordinate" << std::endl;

		p = c;
		std::cout << "p = c" << std::endl;
		std::cout << p.get_x() << std::endl;
	}
}

Coordinate Object::center() {
	double xc, yc;

	for (auto coord : location) {
		xc += coord.get_x();
		yc += coord.get_y();
	}

	xc /= location.size();
	yc /= location.size();

	return Coordinate(xc, yc);
}