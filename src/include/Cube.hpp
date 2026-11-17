#pragma once

#include "Figure.hpp"

class Cube : public Figure {
private:
    double a_;
public:
    Cube();
    explicit Cube(double a);
    double metric() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    Figure* clone() const override;
    double edge() const;
};
