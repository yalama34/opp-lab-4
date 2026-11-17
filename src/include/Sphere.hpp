#pragma once

#include "Figure.hpp"

class Sphere : public Figure {
private:
    double r_;
public:
    Sphere();
    explicit Sphere(double r);
    double metric() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    Figure* clone() const override;
    double radius() const;
};
