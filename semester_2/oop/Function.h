#pragma once
#include <stdexcept>
#include <iostream>
#include <cmath>

class Function {
private:
	size_t id_;
	static size_t counter_;
public:
	Function();

	virtual ~Function() = default;

	size_t get_id() const;

	virtual double evaluate(double x) const = 0;
	virtual int solve(double& solution1, double& solution2) const = 0;
	virtual void print_equation(std::ostream& out) const = 0;
};

class LinearFunction : public Function {
private:
	double a_;
	double b_;
public:
	LinearFunction(double, double);

	double evaluate(double) const override;
	int solve(double&, double&) const override;
	void print_equation(std::ostream&) const override;

	double get_a() const;
	double get_b() const;
};

class QuadraticFunction : public Function {
private:
	double a_;
	double b_;
	double c_;
public:
	QuadraticFunction(double, double, double);

	double evaluate(double) const override;
	int solve(double&, double&) const override;
	void print_equation(std::ostream&) const override;

	double get_a() const;
	double get_b() const;
	double get_c() const;
};