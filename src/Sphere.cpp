#include "Sphere.hpp"
#include <cmath>
#include <numbers>
#include <stdexcept>

Sphere::Sphere() : r_(0.0) {}

Sphere::Sphere(double r) : r_(r) {
    if (!std::isfinite(r) || r < 0.0) {
        throw std::invalid_argument("Invalid sphere radius");
    }
}

double Sphere::metric() const {
    return (4.0 / 3.0) * std::numbers::pi * r_ * r_ * r_;
}

void Sphere::print(std::ostream& os) const {
    os << "Sphere: r=" << r_ << " volume=" << metric();
}

void Sphere::read(std::istream& is) {
    double r;

    if (!(is >> r)) {
        return;
    }

    if (!std::isfinite(r) || r < 0.0) {
        is.setstate(std::ios::failbit);
        return;
    }

    r_ = r;
}

Figure* Sphere::clone() const {
    return new Sphere(*this);
}

double Sphere::radius() const {
    return r_;
}
