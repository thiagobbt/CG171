#include "BezierCurve.h"
#include "Window.h"
#include <cmath>

void BezierCurve::draw() {
	double current_zoom = Window::instance().get_current_zoom();
	size_t n = std::ceil(current_zoom * 100);
	double delta = 1 / n;


}
