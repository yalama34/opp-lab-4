#pragma once

#include "Figure.hpp"

class Cone : public Figure {
private:
    double r_;
    double h_;

public:
    Cone();
    Cone(double r, double h);
    double metric() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    Figure* clone() const override;
    double slantHeight() const;
};
