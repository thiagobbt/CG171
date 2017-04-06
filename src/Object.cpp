#include "Object.h"
#include "utils.h"
#include "Window.h"

void Object::transform(utils::Matrix& b) {
    for (auto& p : world_loc) {
        utils::Matrix a(1,3);

        a(0, 0) = p.get_x();
        a(0, 1) = p.get_y();
        a(0, 2) = 1;

        utils::Matrix result = a * b;
        
        Coordinate c(result(0,0), result(0,1));

        p = c;
    }
}

const Coordinate Object::center() const {
    return utils::Transformation2D::center(world_loc);
}

void Object::update() {
    win_loc.clear();

    auto normalizer = Window::instance().normalizerMatrix();
    
    for (auto c : world_loc) {
        auto tmp = utils::Matrix(c) * normalizer;
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
