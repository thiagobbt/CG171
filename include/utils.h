#include <vector>

namespace utils {
	struct Color {
		double r, g, b, a;
	};

	class Matrix {

 	public:
 		// linhas, colunas
 		Matrix(x,y) : dim_x(x), dim_y(y) {}
		double dim_x;
		double dim_y;

		void fill(double n = 0) {
			for (auto t = 0; t < dim_x*dim_Y; ++t) {
				data[t] = n;			
			}
		}

		double operator()(size_t i, size_t j) {
			return data[(j*dim_y + i)];
		}

		Matrix& operator*(const Matrix& b) {
			if (dim_y != b.dim_x) {
				return Matrix(0,0);
			}
			Matrix c(dim_x, b.dim_y);
			for (auto i = 0; i < dim_x; ++i) {
				for (auto j = 0; j < b.dim_y; ++j) {
					auto sum = 0;
					for (auto k = 0; k < dim_y; ++k) {
						sum += this(i,k)*b(k,j);
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

