#ifndef COORD_H
#define COORD_H

#include <iostream>
#include <cmath>

class Coordinate {
 private:
    double x, y, z, w;

 public:
    Coordinate(const Coordinate&) = default;

    Coordinate(double x = 0, double y = 0, double z = 1, double w = 1)
        : x(x), y(y), z(z), w(w) {}

    const Coordinate operator+(const Coordinate& rhs) const {
        return Coordinate(x + rhs.get_x(), y + rhs.get_y(), z + rhs.get_z(), w + rhs.get_w());
    }

    const Coordinate operator-(const Coordinate& rhs) const {
        return Coordinate(x - rhs.get_x(), y - rhs.get_y(), z - rhs.get_z(), w - rhs.get_w());
    }

    const Coordinate operator-() const {
        return (Coordinate(0, 0, 0) - *this);
    }

    const Coordinate operator/(const Coordinate& rhs) const {
        return Coordinate(x / rhs.get_x(), y / rhs.get_y(), z / rhs.get_z(), w / rhs.get_w());
    }

    const double operator*(const Coordinate& rhs) const {
        double sum = 0;
        for (unsigned i = 0; i < 4; i++) {
            sum += (*this)[i] * rhs[i];
        }
        return sum;
    }

    const Coordinate operator/(const double& rhs) const {
        return Coordinate(x / rhs, y / rhs, z / rhs, w / rhs);
    }

    const Coordinate operator*(const double& rhs) const {
        return Coordinate(x * rhs, y * rhs, z * rhs, w * rhs);
    }

    bool operator!=(const Coordinate& rhs) const {
        if (x != rhs.get_x() ||
            y != rhs.get_y() ||
            z != rhs.get_z() ||
            w != rhs.get_w()) {
            return true;
        }
        return false;
    }

    Coordinate& operator+=(const Coordinate& rhs) {
        x *= rhs.get_x();
        y *= rhs.get_y();
        z *= rhs.get_z();
        w *= rhs.get_w();
        return *this;
    }

    double& operator[](int index) {
        switch (index) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default: return w;
        }
    }

    const double operator[](int index) const {
        switch (index) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default: return w;
        }
    }

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
