#include "BSplineCurve.h"
#include "CurveGTK.h"
#include "DrawingManager.h"
#include "Window.h"
#include "utils.h"
#include <cmath>

BSplineCurve::BSplineCurve(const std::vector<Coordinate>& coordinates, utils::Color c) {
	color = c;
	original_loc = coordinates;
	world_loc = std::vector<Coordinate>();
	drawable_obj = std::make_unique<CurveGTK>(win_loc, c);
	update_coords();
}

void BSplineCurve::update_coords() {
	double current_zoom = Window::instance().get_current_zoom();
	size_t n = std::ceil(current_zoom * 10);
	double delta = 1.0 / n;
	double delta2 = delta * delta;
	double delta3 = delta2 * delta;

	world_loc.clear();

	for (size_t i = 3; i < original_loc.size(); i++) {
		const utils::Matrix gbs_x = {
			{original_loc[i-3][0]}, 
			{original_loc[i-2][0]}, 
			{original_loc[i-1][0]}, 
			{original_loc[i][0]}
		};

		const utils::Matrix gbs_y = {
			{original_loc[i-3][1]}, 
			{original_loc[i-2][1]}, 
			{original_loc[i-1][1]}, 
			{original_loc[i][1]}
		};

		utils::Matrix abcd_x = mbs * gbs_x;
		utils::Matrix abcd_y = mbs * gbs_y;

		utils::Matrix fd_helper = {
			{0, 0, 0, 1},
			{delta3, delta2, delta, 0},
			{6*delta3, 2*delta2, 0, 0},
			{6*delta3, 0, 0, 0},
		};

		utils::Matrix fd_x = fd_helper * abcd_x;
		utils::Matrix fd_y = fd_helper * abcd_y;

		double vx = fd_x(0, 0);
		double vy = fd_y(0, 0);

		world_loc.emplace_back(vx, vy);

		for (double t = 0; t < 1; t += delta) {
			fd_x(0, 0) += fd_x(0, 1);
			fd_x(0, 1) += fd_x(0, 2);
			fd_x(0, 2) += fd_x(0, 3);

			fd_y(0, 0) += fd_y(0, 1);
			fd_y(0, 1) += fd_y(0, 2);
			fd_y(0, 2) += fd_y(0, 3);

			world_loc.emplace_back(fd_x(0, 0), fd_y(0, 0));
		}
	}
}

void BSplineCurve::draw() {
	update_coords();
	DrawingManager::instance().draw(*drawable_obj);
}
