#include "Cone.hpp"

#include <cmath>
#include <numbers>
#include <stdexcept>

Cone::Cone() : r_(0.0), h_(0.0) {}

Cone::Cone(double r, double h) : r_(r), h_(h) {
    if (!std::isfinite(r) || !std::isfinite(h) ||
        r < 0.0 || h < 0.0) {
        throw std::invalid_argument("Invalid cone dimensions");
    }
}

double Cone::metric() const {
    return std::numbers::pi * r_ * r_ * h_ / 3.0;
}

void Cone::print(std::ostream& os) const {
    os << "Cone: r=" << r_
       << " h=" << h_
       << " volume=" << metric();
}

void Cone::read(std::istream& is) {
    double r, h;

    if (!(is >> r >> h)) {
        return;
    }

    if (!std::isfinite(r) || !std::isfinite(h) ||
        r < 0.0 || h < 0.0) {
        is.setstate(std::ios::failbit);
        return;
    }

    r_ = r;
    h_ = h;
}

Figure* Cone::clone() const {
    return new Cone(*this);
}

double Cone::slantHeight() const {
    return std::hypot(r_, h_);
}
