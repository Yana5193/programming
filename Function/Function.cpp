#include "Function.h"
#include<iostream>
using namespace std;

void Function::print(double x) const {
    cout << getName() << "x = " << x << " => y = " << calculate(x) << std::endl;
}

double Function::findMin(double a, double b) const {
    double minimum = calculate(a);
    for (double x = a; x <= b; x+=0.01) {
        if (calculate(x) < minimum) {
            minimum = calculate(x);
        }
    }
    return minimum;
}
double Function::findMax(double a, double b) const {
    double maximum = calculate(a);
    for (double x = a; x <= b; x += 0.01) {
        if (calculate(x) > maximum) {
            maximum = calculate(x);
        }
    }
    return maximum;
}
double Function::Integr(double a, double b) const {
    double n = 10000;   //количество полосок 
    double h = (b - a) / n; //ширина полоски
    double sumArea = 0;

    for (int i = 0; i < n; i++) {
        double x = a + i * h;
        double y = calculate(x);
        sumArea += y * h;
    }
    return sumArea;
}
double Function::Diff(double x) const {
    double h = 0.000001;
    double y1 = calculate(x);
    double y2 = calculate(x + h);
    
    return (y1 - y2) / h;
}
Hiperbola::Hiperbola(double k, double b) : k(k), b(b) {}
double Hiperbola::calculate(double x) const { 
    return (x != 0) ? k / x + b : 0; 
}
string Hiperbola::getName() const { 
    return "Hiperbola"; 
}

Parabola::Parabola(double a, double b, double c) : a(a), b(b), c(c) {}
double Parabola::calculate(double x) const { 
    return a * x * x + b * x + c;
}
string Parabola::getName() const { 
    return "Parabola"; 
}

Exponenta::Exponenta(double a, double k) : a(a), k(k) {}
double Exponenta::calculate(double x) const { 
    return a * exp(k * x); 
}
string Exponenta::getName() const { 
    return "Exponenta"; 
}


