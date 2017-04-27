#ifndef UTILS_H
#define UTILS_H

#include <cstddef>
#include <memory>
#include <type_traits>
#include <utility>

#include <vector>
#include <cassert>
#include <cmath>
#include "Coordinate.h"

namespace std {
    template<class T> struct _Unique_if {
        typedef unique_ptr<T> _Single_object;
    };

    template<class T> struct _Unique_if<T[]> {
        typedef unique_ptr<T[]> _Unknown_bound;
    };

    template<class T, size_t N> struct _Unique_if<T[N]> {
        typedef void _Known_bound;
    };

    template<class T, class... Args>
        typename _Unique_if<T>::_Single_object
        make_unique(Args&&... args) {
            return unique_ptr<T>(new T(std::forward<Args>(args)...));
        }

    template<class T>
        typename _Unique_if<T>::_Unknown_bound
        make_unique(size_t n) {
            typedef typename remove_extent<T>::type U;
            return unique_ptr<T>(new U[n]());
        }

    template<class T, class... Args>
        typename _Unique_if<T>::_Known_bound
        make_unique(Args&&...) = delete;
}

namespace utils {
    struct Color {
        double r, g, b, a;
    };

    class Matrix {
     protected:
        std::vector<double> data;

     public:
        unsigned int dim_x;
        unsigned int dim_y;

        Matrix(unsigned int x, unsigned int y) : dim_x(x), dim_y(y) {
            fill();
        }

        Matrix(const Coordinate& c) : dim_x(1), dim_y(4) {
            data.reserve(4);
            data.push_back(c.get_x());
            data.push_back(c.get_y());
            data.push_back(c.get_z());
            data.push_back(c.get_w());
        }

        Matrix(const std::initializer_list<std::initializer_list<double>>& matrix) {
            dim_x = matrix.size();
            dim_y = (*matrix.begin()).size();
            for (auto row : matrix) {
                for (auto value : row) {
                    data.push_back(value);
                }
            }
        }

        void fill(double n = 0) {
            data.reserve(dim_x * dim_y);
            for (unsigned int t = 0; t < dim_x * dim_y; ++t) {
                data.push_back(n);
            }
        }

        Coordinate to_coord() {
            return Coordinate((*this)(0, 0), (*this)(0, 1), (*this)(0, 2), (*this)(0, 3));
        }

        double& operator()(unsigned int j, unsigned int i) {
            return data[j*dim_y + i];
        }

        const double& operator()(unsigned int j, unsigned int i) const {
            return data[j*dim_y + i];
        }

        Matrix operator*(const Matrix& b) {
            assert(dim_y == b.dim_x);

            Matrix c(dim_x, b.dim_y);
            for (unsigned int i = 0; i < dim_x; ++i) {
                for (unsigned int j = 0; j < b.dim_y; ++j) {
                    double sum = 0;
                    for (unsigned int k = 0; k < dim_y; ++k) {
                        sum += (*this)(i, k) * b(k, j);
                    }
                    c(i,j) = sum;
                }
            }
            return c;
        }

        Matrix operator/(const int& b) {
            Matrix c(dim_x, dim_y);

            for (auto d : data) {
                c.data.clear();
                c.data.push_back(d / b);
            }
            return c;
        }

        Matrix operator*(const Coordinate& rhs) {
            Matrix b(rhs);
            return (*this) * b;
        }
    };

    namespace Transformation2D {
        inline Matrix rotation_matrix(double angle) {
            utils::Matrix a(3,3);
            auto real_angle = angle * M_PI / 180;
            a(0, 0) = cos(real_angle);
            a(0, 1) = - sin(real_angle);
            a(1, 0) = sin(real_angle);
            a(1, 1) = cos(real_angle);
            a(2, 2) = 1;

            return a;
        }

        inline Matrix translation_matrix(double dx, double dy) {
            utils::Matrix a(3,3);
            a(0, 0) = 1;
            a(1, 1) = 1;
            a(2, 2) = 1;
            a(2, 0) = dx;
            a(2, 1) = dy;

            return a;
        }

        inline Matrix scaling_matrix(double dx, double dy) {
            Matrix a(3,3);
            a(0, 0) = dx;
            a(1, 1) = dy;
            a(2, 2) = 1;

            return a;
        }

        inline Coordinate center(const std::vector<Coordinate>& coords) {
            double xc = 0;
            double yc = 0;

            for (auto coord : coords) {
                xc += coord.get_x();
                yc += coord.get_y();
            }

            xc /= coords.size();
            yc /= coords.size();

            return Coordinate(xc, yc);
        }
    }

    namespace Transformation3D {
        inline Matrix rotation_matrix_x(double angle) {
            auto real_angle = angle * M_PI / 180;
            Matrix r = {
                {1, 0,                0,               0},
                {0, cos(real_angle),  sin(real_angle), 0},
                {0, -sin(real_angle), cos(real_angle), 0},
                {0, 0,                0,               1}
            };

            return r;
        }

        inline Matrix rotation_matrix_y(double angle) {
            auto real_angle = angle * M_PI / 180;
            Matrix r = {
                {cos(real_angle), 0, -sin(real_angle), 0},
                {0,               1, 0,                0},
                {sin(real_angle), 0, cos(real_angle),  0},
                {0,               0, 0,                1}
            };

            return r;
        }

        inline Matrix rotation_matrix_z(double angle) {
            auto real_angle = angle * M_PI / 180;
            Matrix r = {
                {cos(real_angle),  sin(real_angle), 0, 0},
                {-sin(real_angle), cos(real_angle), 0, 0},
                {0,                0,               1, 0},
                {0,                0,               0, 1}
            };

            return r;
        }

        inline Matrix scaling_matrix(const std::vector<double>& scale) {
            Matrix a(4, 4);

            for (size_t i = 0; i < 4; ++i) {
                a(i,i) = scale[i];
            }

            a(3,3) = 1;

            return a;
        }

        inline Coordinate center(const std::vector<Coordinate>& coords) {
            double xc = 0;
            double yc = 0;
            double zc = 0;

            for (auto coord : coords) {
                xc += coord.get_x();
                yc += coord.get_y();
                zc += coord.get_z();
            }

            xc /= coords.size();
            yc /= coords.size();
            zc /= coords.size();

            return Coordinate(xc, yc, zc);
        }
    }
}

#endif /* UTILS_H */
