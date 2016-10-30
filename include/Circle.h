#ifndef CIRCLE_H
#define CIRCLE_H
#include "Shape.h"

class Circle : public Shape
{
public:
    Circle(Point_t center, double radius);
    ~Circle();
    virtual double Area() const;
    virtual double Perimeter() const;
    virtual string Description() const;
private:
    Point_t _center;
    double _radius;
};

#endif // CIRCLE_H
