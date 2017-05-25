#ifndef COORD_H
#define COORD_H

#include <iostream>
#include <cmath>

namespace utils {
    class Matrix;
}

class Coordinate {
 private:
    double x, y, z, w;

 public:
    Coordinate(const Coordinate&) = default;
    Coordinate(double x = 0, double y = 0, double z = 1, double w = 1);

    const Coordinate operator+(const Coordinate& rhs) const;
    const Coordinate operator-(const Coordinate& rhs) const;
    const Coordinate operator-() const;
    const Coordinate operator/(const Coordinate& rhs) const;
    const double operator*(const Coordinate& rhs) const;
    const Coordinate operator/(const double& rhs) const;
    const Coordinate operator*(const double& rhs) const;
    const utils::Matrix operator*(const utils::Matrix& rhs) const;
    bool operator!=(const Coordinate& rhs) const;
    Coordinate& operator*=(const Coordinate& rhs);
    Coordinate& operator*=(const utils::Matrix& rhs);
    double& operator[](int index);
    const double operator[](int index) const;

    friend std::ostream& operator<<(std::ostream& out, const Coordinate& c) {
        out << "v " << c.x << " " << c.y << " " << c.z;
        return out;
    }

    const double get_x() const { return x; }
    const double get_y() const { return y; }
    const double get_z() const { return z; }
    const double get_w() const { return w; }

    const double norm() const {
        auto sum = x*x + y*y + z*z;
        return std::sqrt(sum);
    }
};

#endif /* COORD_H */
