#pragma once
#include<iostream>
using namespace std;
class Function {
public:
	virtual ~Function() {}

	virtual double calculate(double x) const = 0;
	virtual string getName() const = 0;
	void print(double x) const;

	virtual double findMin(double a,double b) const;
	virtual double findMax(double a, double b) const;
	virtual double Integr(double a, double b) const;
	virtual double Diff(double x) const;

};
class Hiperbola:public Function {
public:
	double k, b;
	Hiperbola(double k = 1.0, double b = 0.0);
	double calculate(double x) const override;
	string getName() const override;
};
class Parabola :public Function {
public:
	double a, b, c;
	Parabola(double a = 1.0, double b = 0.0, double c = 0.0);
	double calculate(double x) const override;
	string getName() const override;
};
class Exponenta :public Function {
public:
	double a,k;
	Exponenta(double a = 1.0, double k = 1.0);
	double calculate(double x) const override;
	string getName() const override;
};