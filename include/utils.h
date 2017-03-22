#ifndef _UTILS_H_
#define _UTILS_H_

#include <vector>
#include <cassert>
#include <iostream>


namespace utils {
#define PI 3.14159265

struct Color {
	double r, g, b, a;
};

class Matrix {
 protected:
	std::vector<double> data;

 public:
	unsigned int dim_x;
	unsigned int dim_y;

	// linhas, colunas
	Matrix(unsigned int x, unsigned int y) : dim_x(x), dim_y(y) {
		fill();
	}

	void fill(double n = 0) {
		data.reserve(dim_x * dim_y);
		for (unsigned int t = 0; t < dim_x * dim_y; ++t) {
			data.push_back(n);
		}
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
};
}

#endif /* _UTILS_H_ */