/* copyright vfreitas & thiagobbt */

#ifndef _COORD_H_
#define _COORD_H_

class Coordinate {
 private:
 	double x, y, z, w;
 public:
 	Coordinate(const Coordinate&) {}
 	Coordinate(double x = 0, double y = 0, double z = 0, double w = 0)
 		: x(x), y(y), z(z), w(w) {}

 	void sum_coords(double a = 0, double b = 0, double c = 0, double d = 0) {
 		x += a;
 		y += b;
 		z += c;
 		w += d;
 	}

 	double get_x() { return x; }
 	double get_y() { return y; }
 	double get_z() { return z; }
 	double get_w() { return w; }
};

#endif /* _COORD_H_ */