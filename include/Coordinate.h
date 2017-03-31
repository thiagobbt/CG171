/* copyright vfreitas & thiagobbt */

#ifndef _COORD_H_
#define _COORD_H_

#include <iostream>

class Coordinate {
 private:
    double x, y, z, w;

 public:
    Coordinate(const Coordinate&) = default;
    Coordinate(double x = 0, double y = 0, double z = 0, double w = 0)
        : x(x), y(y), z(z), w(w) {}

    void sum_coords(double a = 0, double b = 0, double c = 0, double d = 0) {
        x += a;
        y += b;
        z += c;
        w += d;
    }

    Coordinate operator+(const Coordinate& rhs) {
        return Coordinate(x + rhs.get_x(), y + rhs.get_y(), z + rhs.get_z());
    }

    Coordinate operator/(const Coordinate& rhs) {
        return Coordinate(x / rhs.get_x(), y / rhs.get_y(), z / rhs.get_z());
    }

     Coordinate operator*(const Coordinate& rhs) {
        return Coordinate(x * rhs.get_x(), y * rhs.get_y(), z * rhs.get_z());
    }

    Coordinate operator/(const double& rhs) {
        return Coordinate(x / rhs, y / rhs, z / rhs);
    }

    Coordinate& operator*=(const Coordinate& rhs) {
        x *= rhs.get_x();
        y *= rhs.get_y();
        z *= rhs.get_z();
        return *this;
    }

    const double get_x() const { return x; }
    const double get_y() const { return y; }
    const double get_z() const { return z; }
    const double get_w() const { return w; }
};

inline std::ostream& operator<<(std::ostream& out, const Coordinate& c) {
    out << "v " << c.get_x() << " " << c.get_y() << " " << c.get_z();
    return out;
}

#endif /* _COORD_H_ */