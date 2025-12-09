#include "vector_impl.h"

Vector::Vector() {
    std::cout << "Default.\n";
}

Vector::Vector(size_t n) : size_(n), capacity_(n), data_(new int[capacity_]) {
    std::cout << "User defined.\n";
    for (size_t i = 0; i < n; ++i) {
        data_[i] = 0;
    }
}

Vector::Vector(const Vector& other)
    : size_(other.size_), capacity_(other.capacity_), data_(new int[capacity_]) {
    std::cout << "Copy ctor.\n";
    std::copy(other.data_, other.data_ + size_, data_);
}

Vector::Vector(std::initializer_list<char> list)
    : size_(list.size()), capacity_(list.size()), data_(new int[capacity_]) {

    size_t i = 0;

    for (int item : list) {
        data_[i] = item;
        ++i;
    }
}

Vector::~Vector() {
    std::cout << "Destructor.\n";
    delete[] data_;
}

Vector& Vector::operator=(const Vector& other) {
    std::cout << "operator=.\n";

    if (this == &other) {
        return *this;
    }

    Vector copy(other);
    Swap(copy);

    return *this;
}

void Vector::Swap(Vector& other) {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

int& Vector::operator[](size_t index) {
    return data_[index];
}

const int& Vector::operator[](size_t index) const {
    return data_[index];
}

int& Vector::At(size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Error: index out of range");
    }
    return data_[index];
}

const int& Vector::At(size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Error: index out of range");
    }
    return data_[index];
}

size_t Vector::Size() const {
    return size_ == 0u ? 0u : size_;
}

size_t Vector::Capacity() const {
    return capacity_ == 0u ? 0u : capacity_;
}

void Vector::PushBack(int element) {
    if (capacity_ <= size_) {
        if (capacity_ == 0) {
            capacity_ = 1;
        }
        Vector temp(capacity_ * 2);
        Swap(temp);
    }
    data_[size_++] = element;
}

void Vector::PopBack() {
    if (size_ > 0) {
        data_[size_ - 1] = 0;
        --size_;
    }
}

void Vector::Clear() {
    while (size_ > 0) {
        data_[size_ - 1] = 0;
        --size_;
    }
}

void Vector::Reserve(size_t other_capacity) {
    if (capacity_ < other_capacity) {
        Vector temp(other_capacity);
        Swap(temp);
    }
}

std::ostream& operator<<(std::ostream& out, const Vector& vect) {
    if (vect.data_ == nullptr) {
        out << "[]\n";
    } else {
        out << "[";
        for (size_t i = 0; i < vect.Size(); ++i) {
            out << vect[i];
        }
        out << "]\n";
    }
    return out;
}
