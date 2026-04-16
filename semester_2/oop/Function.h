#pragma once
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <vector>

enum Function_ID { LinearFunction_ID = 0, QuadraticFunction_ID };

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

	static Function* create_function(Function_ID, double, double, double);
};

class LinearFunction : public Function {
private:
	double a_;
	double b_;
public:
	LinearFunction(double, double);
	LinearFunction(const LinearFunction&);
	LinearFunction(LinearFunction&&) noexcept;
	LinearFunction& operator=(const LinearFunction&);
	LinearFunction& operator=(LinearFunction&&) noexcept;
	~LinearFunction() override = default;

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
	QuadraticFunction(const QuadraticFunction&);
	QuadraticFunction(QuadraticFunction&&) noexcept;
	QuadraticFunction& operator=(const QuadraticFunction&);
	QuadraticFunction& operator=(QuadraticFunction&&) noexcept;
	~QuadraticFunction() override = default;

	double evaluate(double) const override;
	int solve(double&, double&) const override;
	void print_equation(std::ostream&) const override;

	double get_a() const;
	double get_b() const;
	double get_c() const;
};

class Factory {
public:
	virtual Function* create_function(double, double, double) = 0;
	virtual ~Factory() {}
};

class LinearFactory : public Factory {
public:
	Function* create_function(double, double, double) override;
};

class QuadraticFactory : public Factory {
public:
	Function* create_function(double, double, double) override;
};

class CompositeFunction : public Function {
private:
	std::vector<Function*> functions;
public:
	void add_function(Function*);
	~CompositeFunction();
	double evaluate(double x) const override { return 0; }
	int solve(double& solution1, double& solution2) const override { return 0; }
	void print_equation(std::ostream& out) const override {}
	int size() { return functions.size(); }
	Function* at(int i) { return functions[i]; }
};