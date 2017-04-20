#include "BSplineCurve.h"
#include "Window.h"
#include "CurveGTK.h"
#include "DrawingManager.h"
#include <cmath>

BSplineCurve::BSplineCurve(const std::vector<Coordinate>& coordinates, utils::Color c) {
	color = c;
	original_loc = coordinates;
	world_loc = std::vector<Coordinate>();
    drawable_obj = std::unique_ptr<CurveGTK>(new CurveGTK(win_loc, c));
    update_coords();
}

void BSplineCurve::update_coords() {
	std::cout << "BSplineCurve::update_coords" << std::endl;
	double current_zoom = Window::instance().get_current_zoom();
	size_t n = std::ceil(current_zoom * 100);
	double delta = 1.0 / n;

	world_loc.clear();

	int num_curves = ((original_loc.size()-4)/3) + 1;

	for (int i = 0; i < num_curves; i++) {
		for (double t = 0; t < 1; t += delta) {
			double t2 = t * t;
			double t3 = t2 * t;

			utils::Matrix t_m = {{t3, t2, t, 1}};

			utils::Matrix gb_x = {
				{original_loc[i*3][0]},
				{original_loc[i*3+1][0]}, 
				{original_loc[i*3+2][0]},
				{original_loc[i*3+3][0]},
			};

			utils::Matrix gb_y = {
				{original_loc[i*3][1]},
				{original_loc[i*3+1][1]}, 
				{original_loc[i*3+2][1]},
				{original_loc[i*3+3][1]},
			};

			auto tmp = t_m * mb;
			auto x_m = tmp * gb_x;
			auto y_m = tmp * gb_y;

			world_loc.emplace_back(x_m(0, 0), y_m(0, 0));
		}
	}
}

void BSplineCurve::draw() {
	std::cout << "BSplineCurve::draw" << std::endl;
	update_coords();
	DrawingManager::instance().draw(*drawable_obj);
}
