#include "Circle.h"

double Circle:: Area() const {
    return PI * _radius * _radius;
}
double Circle:: Perimeter() const {
    return 2 * PI * _radius;
}
