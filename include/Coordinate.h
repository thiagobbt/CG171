/* copyright vfreitas & thiagobbt */

#ifndef _COORD_H_
#define _COORD_H_

class Coordinate {
 private:
 	double x, y, z, w;
 public:
 	Coordinate(const Coordinate&);
 	Coordinate(double, double, double, double);

 	double get_x() { return x; }
 	double get_y() { return y; }
 	double get_z() { return z; }
 	double get_w() { return w; }
};

#endif /* _COORD_H_ */