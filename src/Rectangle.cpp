#include "Rectangle.h"

double Rectangle:: Area() const {
    return _width * _height;
}
double Rectangle:: Perimeter() const {
    return 2 * (_width + _height);
}
