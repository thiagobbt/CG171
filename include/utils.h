#ifndef _UTILS_H_
#define _UTILS_H_

#include <vector>
#include <cassert>



namespace utils {
	#define PI 3.14159265

	struct Color {
		double r, g, b, a;
	};

	class Matrix {

 	public:
		unsigned int dim_x;
		unsigned int dim_y;

 		// linhas, colunas
 		Matrix(unsigned int x, unsigned int y) : dim_x(x), dim_y(y) {}

		void fill(double n = 0) {
			for (unsigned int t = 0; t < dim_x*dim_y; ++t) {
				data.push_back(n);
			}
		}

		void add(unsigned int i, unsigned int j, double dat) {
			(*this)(i,j) = dat;
		}

		double& operator()(unsigned int i, unsigned int j) {
			return data[(j*dim_y + i)];
		}

		const double& operator()(unsigned int i, unsigned int j) const {
			return data[(j*dim_y + i)];
		}

		Matrix operator*(const Matrix& b) {
			assert(dim_y == b.dim_x);

			Matrix c(dim_x, b.dim_y);
			for (unsigned int i = 0; i < dim_x; ++i) {
				for (unsigned int j = 0; j < b.dim_y; ++j) {
					unsigned int sum = 0;
					for (unsigned int k = 0; k < dim_y; ++k) {
						sum += (*this)(i,k) * b(k, j);
					}
					c(i,j) = sum;
				}
			}
			return c;
		}

	protected:
		std::vector<double> data;
	
	};

}

#endif /* _UTILS_H_ */