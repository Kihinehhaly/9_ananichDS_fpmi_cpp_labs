#include "Function.h"

size_t Function::counter_ = 0;

Function::Function() : id_(++counter_) {}

size_t Function::get_id() const {
	return id_;
}


LinearFunction::LinearFunction(double a, double b) : a_(a), b_(b) {}

LinearFunction::LinearFunction(const LinearFunction& other) : a_(other.a_), b_(other.b_) {}

LinearFunction::LinearFunction(LinearFunction&& other) noexcept : a_(other.a_), b_(other.b_) {
	other.a_ = 0;
	other.b_ = 0;
}

LinearFunction& LinearFunction::operator=(const LinearFunction& rhs) {
	if (this != &rhs) {
		a_ = rhs.a_;
		b_ = rhs.b_;
	}
	return *this;
}

LinearFunction& LinearFunction::operator=(LinearFunction&& rhs) noexcept {
	if (this != &rhs) {
		a_ = rhs.a_;
		b_ = rhs.b_;
		rhs.a_ = 0;
		rhs.b_ = 0;
	}
	return *this;
}

double LinearFunction::evaluate(double x) const {
	return a_ * x + b_;
}

int LinearFunction::solve(double& solution1, double& solution2) const {
	if (a_ == 0) {
		return 0;
	}
	solution1 = -b_ / a_;
	solution2 = solution1;
	return 1;
}

void LinearFunction::print_equation(std::ostream& out) const {
	out << a_ << "x + " << b_ << " = 0";
}

double LinearFunction::get_a() const {
	return a_;
}

double LinearFunction::get_b() const {
	return b_;
}


QuadraticFunction::QuadraticFunction(double a, double b, double c) : a_(a), b_(b), c_(c) {
	if (a == 0) {
		throw std::invalid_argument("You can't enter a=0");
	}
}

QuadraticFunction::QuadraticFunction(const QuadraticFunction& other) : a_(other.a_), b_(other.b_), c_(other.c_) {}

QuadraticFunction::QuadraticFunction(QuadraticFunction&& other) noexcept : a_(other.a_), b_(other.b_), c_(other.c_) {
	other.a_ = 1;
	other.b_ = 0;
	other.c_ = 0;
}

QuadraticFunction& QuadraticFunction::operator=(const QuadraticFunction& rhs) {
	if (this != &rhs) {
		a_ = rhs.a_;
		b_ = rhs.b_;
		c_ = rhs.c_;
	}
	return *this;
}

QuadraticFunction& QuadraticFunction::operator=(QuadraticFunction&& rhs) noexcept {
	if (this != &rhs) {
		a_ = rhs.a_;
		b_ = rhs.b_;
		c_ = rhs.c_;
		rhs.a_ = 1;
		rhs.b_ = 0;
		rhs.c_ = 0;
	}
	return *this;
}

double QuadraticFunction::evaluate(double x) const {
	return a_ * x * x + b_ * x + c_;
}

int QuadraticFunction::solve(double& solution1, double& solution2) const {
	double d = b_ * b_ - 4 * a_ * c_;

	if (d < 0) {
		return 0;
	}

	if (d == 0) {
		solution1 = -b_ / (2 * a_);
		solution2 = solution1;
		return 1;
	}

	solution1 = (-b_ + sqrt(d)) / (2 * a_);
	solution2 = (-b_ - sqrt(d)) / (2 * a_);
	return 2;

}

void QuadraticFunction::print_equation(std::ostream& out) const {
	out << a_ << "x^2 + " << b_ << "x + " << c_ << " = 0";
}

double QuadraticFunction::get_a() const {
	return a_;
}

double QuadraticFunction::get_b() const {
	return b_;
}

double QuadraticFunction::get_c() const {
	return c_;
}