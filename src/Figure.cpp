#include "Figure.hpp"

#include <cmath>

Figure::operator double() const {
    return metric();
}

bool operator==(const Figure& lhs, const Figure& rhs) {
    constexpr double eps = 1e-6;
    return std::abs(lhs.metric() - rhs.metric()) < eps;
}

std::ostream& operator<<(std::ostream& os, const Figure& figure) {
    figure.print(os);
    return os;
}

std::istream& operator>>(std::istream& is, Figure& figure) {
    figure.read(is);
    return is;
}
