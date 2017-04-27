#include "Object.h"
#include "Window.h"
#include "utils.h"

void Object::transform(utils::Matrix& b) {
	for (auto& p : world_loc) {
		utils::Matrix a(p, 4);
		utils::Matrix result = a * b;

		Coordinate c(result(0, 0), result(0, 1), result(0, 2), result(0, 3));

		p = c;
	}
}

const Coordinate Object::center() const {
	return utils::Transformation3D::center(world_loc);
}

void Object::update() {
	win_loc.clear();

	auto normalizer = Window::instance().normalizerMatrix();

	for (auto c : world_loc) {
		auto tmp = utils::Matrix(c, 4) * normalizer;
		win_loc.push_back(tmp.to_coord());
	}
}

const int Object::num_coords() const {
	return world_loc.size();
}

std::ostream& operator<<(std::ostream& out, const Object& obj) {
	for (auto c : obj.world_loc) {
		out << c << std::endl;
	}

	return out;
}
