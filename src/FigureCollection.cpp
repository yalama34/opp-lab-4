#include "FigureCollection.hpp"

#include <stdexcept>
#include <utility>

FigureCollection::FigureCollection()
    : data_(nullptr), size_(0), capacity_(0) {}

FigureCollection::~FigureCollection() {
    clear();
}

void FigureCollection::clear() noexcept {
    for (std::size_t i = 0; i < size_; ++i) {
        delete data_[i];
    }

    delete[] data_;

    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}

void FigureCollection::reserve(std::size_t newCapacity) {
    if (newCapacity <= capacity_) {
        return;
    }

    Figure** newData = new Figure*[newCapacity];

    for (std::size_t i = 0; i < size_; ++i) {
        newData[i] = data_[i];
    }

    delete[] data_;

    data_ = newData;
    capacity_ = newCapacity;
}

FigureCollection::FigureCollection(const FigureCollection& other)
    : data_(nullptr), size_(0), capacity_(0) {
    try {
        reserve(other.size_);

        for (std::size_t i = 0; i < other.size_; ++i) {
            data_[i] = other.data_[i]->clone();
            ++size_;
        }
    } catch (...) {
        clear();
        throw;
    }
}

FigureCollection& FigureCollection::operator=(
    const FigureCollection& other
) {
    if (this == &other) {
        return *this;
    }

    FigureCollection temp(other);

    std::swap(data_, temp.data_);
    std::swap(size_, temp.size_);
    std::swap(capacity_, temp.capacity_);

    return *this;
}

FigureCollection::FigureCollection(FigureCollection&& other) noexcept
    : data_(other.data_),
      size_(other.size_),
      capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

FigureCollection& FigureCollection::operator=(
    FigureCollection&& other
) noexcept {
    if (this == &other) {
        return *this;
    }

    clear();

    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;

    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;

    return *this;
}

void FigureCollection::add(Figure* figure) {
    if (figure == nullptr) {
        throw std::invalid_argument("Null figure");
    }

    if (size_ == capacity_) {
        reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }

    data_[size_] = figure;
    ++size_;
}

void FigureCollection::remove(std::size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Invalid figure index");
    }

    delete data_[index];

    for (std::size_t i = index; i + 1 < size_; ++i) {
        data_[i] = data_[i + 1];
    }

    --size_;
    data_[size_] = nullptr;
}

Figure& FigureCollection::operator[](std::size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Invalid figure index");
    }

    return *data_[index];
}

const Figure& FigureCollection::operator[](
    std::size_t index
) const {
    if (index >= size_) {
        throw std::out_of_range("Invalid figure index");
    }

    return *data_[index];
}

std::size_t FigureCollection::size() const noexcept {
    return size_;
}

bool FigureCollection::empty() const noexcept {
    return size_ == 0;
}

double FigureCollection::totalMetric() const {
    double total = 0.0;

    for (std::size_t i = 0; i < size_; ++i) {
        total += data_[i]->metric();
    }

    return total;
}
