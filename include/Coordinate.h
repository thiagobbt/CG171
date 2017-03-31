#ifndef COORD_H
#define COORD_H

#include <iostream>

class Coordinate {
 private:
    double x, y, z, w;

 public:
    Coordinate(const Coordinate&) = default;
    Coordinate(double x = 0, double y = 0, double z = 1, double w = 1)
        : x(x), y(y), z(z), w(w) {}

    Coordinate operator+(const Coordinate& rhs) {
        return Coordinate(x + rhs.get_x(), y + rhs.get_y(), z + rhs.get_z(), w + rhs.get_w());
    }

    Coordinate operator-(const Coordinate& rhs) {
        return Coordinate(x - rhs.get_x(), y - rhs.get_y(), z - rhs.get_z(), w - rhs.get_w());
    }

    Coordinate operator/(const Coordinate& rhs) {
        return Coordinate(x / rhs.get_x(), y / rhs.get_y(), z / rhs.get_z(), w / rhs.get_w());
    }

    Coordinate operator*(const Coordinate& rhs) {
        return Coordinate(x * rhs.get_x(), y * rhs.get_y(), z * rhs.get_z(), w * rhs.get_w());
    }

    Coordinate operator/(const double& rhs) {
        return Coordinate(x / rhs, y / rhs, z / rhs, w / rhs);
    }

    Coordinate& operator*=(const Coordinate& rhs) {
    	x += rhs.get_x();
        y += rhs.get_y();
        z += rhs.get_z();
        w += rhs.get_w();
        return *this;
    }

    Coordinate& operator+=(const Coordinate& rhs) {
        x *= rhs.get_x();
        y *= rhs.get_y();
        z *= rhs.get_z();
        w *= rhs.get_w();
        return *this;
    }

    const double get_x() const { return x; }
    const double get_y() const { return y; }
    const double get_z() const { return z; }
    const double get_w() const { return w; }
};

inline std::ostream& operator<<(std::ostream& out, const Coordinate& c) {
    return out;
}

#endif /* COORD_H */