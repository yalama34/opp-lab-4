#pragma once

#include <iostream>

class Figure {
public:
    virtual ~Figure() = default;
    virtual double metric() const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;
    virtual Figure* clone() const = 0;
    explicit operator double() const;
};

bool operator==(const Figure& lhs, const Figure& rhs);
std::ostream& operator<<(std::ostream& os, const Figure& figure);
std::istream& operator>>(std::istream& is, Figure& figure);
