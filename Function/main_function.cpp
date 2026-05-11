#include "Function.h"
#include <iostream>
#include <iomanip> 
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    cout << fixed << setprecision(3);
    // y = 10/x + 2
    Hiperbola gip(10.0, 2.0);

    // y = 1*x^2 - 4*x + 4 
    Parabola par(1.0, -4.0, 4.0);

    //y = 1 * e^(0.5x)
    Exponenta expn(1.0, 0.5);

    Function* functions[3];
    functions[0] = &gip;
    functions[1] = &par;
    functions[2] = &expn;

    for (int i = 0; i < 3; i++) {
        cout << "функця: " << functions[i]->getName() << endl;

        //значения в точке
        double x_point = 2.0;
        functions[i]->print(x_point);

        double a = 1.0, b = 9.0;
        cout << "Минимум на [" << a << ", " << b << "]: " << functions[i]->findMin(a, b) << endl;
        cout << "Максимум на [" << a << ", " << b << "]: " << functions[i]->findMax(a, b) << endl;
        cout << "Интеграл от " << a << " до " << b << ": " << functions[i]->Integr(a, b) << endl;
        cout << "Производная в точке x = " << x_point << ": " << functions[i]->Diff(x_point) << endl;

        cout << endl;
    }

    return 0;

}