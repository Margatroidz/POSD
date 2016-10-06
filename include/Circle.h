#ifndef CIRCLE_H
#define CIRCLE_H
#include "Shape.h"

class Circle : public Shape
{
public:
    Circle(Point_t center, double radius):
        _center(center), _radius(radius) { if(radius < 0) throw ERROR; };
    ~Circle() {};
    virtual double Area() const;
    virtual double Perimeter() const;
private:
    Point_t _center;
    double _radius;
};

#endif // CIRCLE_H
