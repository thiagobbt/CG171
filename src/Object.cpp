/* copyright vfreitas & thiagobbt */

#include "Object.h"
#include "utils.h"
#include <iostream>


// THIS HAVE TO BE TESTED: use of not of reference on P
void Object::transform(const utils::Matrix& b) {
	for (auto& p : location) {
		std::cout << p.get_x() << std::endl;
		utils::Matrix a(1,3);
		a.add(0, 0, p.get_x());
		a.add(0, 1, p.get_y());
		a.add(0, 2, 1);
		a = a*b;
		Coordinate c (a(0,0), a(0,1));
		p = c;
		std::cout << p.get_x() << std::endl;
	}
}