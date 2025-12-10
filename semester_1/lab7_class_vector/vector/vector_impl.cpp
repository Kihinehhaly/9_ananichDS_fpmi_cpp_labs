#include "vector_impl.h"

Vector::Vector() {}

Vector::Vector(size_t n) : size_(n), capacity_(n), data_(new int[capacity_]) {
    for (size_t i = 0; i < n; ++i) {
        data_[i] = 0;
    }
}

Vector::Vector(const Vector& other)
    : size_(other.size_), capacity_(other.capacity_), data_(new int[capacity_]) {
    std::copy(other.data_, other.data_ + size_, data_);
}

Vector::Vector(std::initializer_list<int> list)
    : size_(list.size()), capacity_(list.size()), data_(new int[capacity_]) {

    size_t i = 0;

    for (int item : list) {
        data_[i] = item;
        ++i;
    }
}

Vector::~Vector() {
    delete[] data_;
}

Vector& Vector::operator=(const Vector& other) {
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
    if (size_ >= capacity_) {
        size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        Reserve(new_capacity);
    }
    data_[size_++] = element;
}

void Vector::PopBack() {
    if (size_ > 0) {
        --size_;
    }
}

void Vector::Clear() {
    while (size_ > 0) {
        --size_;
    }
}

void Vector::Reserve(size_t other_capacity) {
    if (capacity_ >= other_capacity) {
        return;
    }

    int* new_data = new int[other_capacity];

    for (size_t i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
    }

    delete[] data_;

    data_ = new_data;
    capacity_ = other_capacity;
}

std::ostream& operator<<(std::ostream& out, const Vector& vect) {
    if (vect.data_ == nullptr) {
        out << "[]";
    } else {
        out << "[";
        for (size_t i = 0; i < vect.Size() - 1; ++i) {
            out << vect[i] << ", ";
        }
        out << vect[vect.Size() - 1] << "]";
    }
    return out;
}
