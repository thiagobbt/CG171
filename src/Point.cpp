/* vfreitas & thiagobbt */

#include "Point.h"
#include "PointGTK.h"


Point::Point(std::vector<Coordinate> coordinates, utils::Color c) 
		: location(coordinates), color(c) {
	drawable_obj = new PointGTK(location, c, false);
}

Point::Point() {
	location = std::vector<Coordinate>(1);
}

Point::~Point() { 
	Object::~Object();
}

void Point::draw() {
	DrawingManager::instance().draw(*drawable_obj);
}

// Dx, Dy = Parâmetros da Translação
// Sx, Sy = Parâmetros do escalonamento
// Rx, Ry = Referência da rotação
// Teta = ângulo de rotação
void Point::t(double dx, double dy, double sx, double sy, 
	double rx, double ry, double teta) {

	
}