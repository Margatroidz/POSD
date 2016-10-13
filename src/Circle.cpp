#include "Circle.h"

Circle :: Circle(Point_t center, double radius):
    _center(center), _radius(radius)
{
    if(radius < 0) throw ERROR;
}

Circle :: ~Circle()
{
}

double Circle:: Area() const
{
    return PI * _radius * _radius;
}
double Circle:: Perimeter() const
{
    return 2 * PI * _radius;
}
