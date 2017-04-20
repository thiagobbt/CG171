#include "Curve.h"
#include "DrawingManager.h"
#include "Window.h"

void Curve::clip() {
	if (win_loc.size() == 0) return;
	std::vector<Coordinate> tmp;
	for (size_t i = 0; i < win_loc.size() - 1; i++) {
		std::vector<Coordinate> v = {win_loc[i], win_loc[i+1]};
		Window::instance().clipLine(v);

		for (auto c : v) {
			tmp.push_back(c);
		}
	}

	win_loc = tmp;
}
