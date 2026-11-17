#pragma once

#include "Figure.hpp"

class FigureCollection {
private:
    Figure** data_;
    std::size_t size_;
    std::size_t capacity_;
    void reserve(std::size_t newCapacity);
    void clear() noexcept;

public:
    FigureCollection();
    ~FigureCollection();
    FigureCollection(const FigureCollection& other);
    FigureCollection& operator=(const FigureCollection& other);
    FigureCollection(FigureCollection&& other) noexcept;
    FigureCollection& operator=(FigureCollection&& other) noexcept;
    void add(Figure* figure);
    void remove(std::size_t index);
    Figure& operator[](std::size_t index);
    const Figure& operator[](std::size_t index) const;
    std::size_t size() const noexcept;
    bool empty() const noexcept;
    double totalMetric() const;
};
