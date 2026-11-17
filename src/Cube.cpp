#include "Cube.hpp"

#include <cmath>
#include <stdexcept>

Cube::Cube() : a_(0.0) {}

Cube::Cube(double a) : a_(a) {
    if (!std::isfinite(a) || a < 0.0) {
        throw std::invalid_argument("Invalid cube edge");
    }
}

double Cube::metric() const {
    return a_ * a_ * a_;
}

void Cube::print(std::ostream& os) const {
    os << "Cube: a=" << a_ << " volume=" << metric();
}

void Cube::read(std::istream& is) {
    double a;
    if (!(is >> a)) {
        return;
    }
    if (!std::isfinite(a) || a < 0.0) {
        is.setstate(std::ios::failbit);
        return;
    }

    a_ = a;
}

Figure* Cube::clone() const {
    return new Cube(*this);
}

double Cube::edge() const {
    return a_;
}
