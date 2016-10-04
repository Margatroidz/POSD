#include "Circle.h"

double Circle:: area()
{
    return PI * _radius * _radius;
}
double Circle:: perimeter()
{
    return 2 * PI * _radius;
}
