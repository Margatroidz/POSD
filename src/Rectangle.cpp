#include "Rectangle.h"

double Rectangle:: area()
{
    return _width * _height;
}
double Rectangle:: perimeter()
{
    return 2 * (_width + _height);
}
