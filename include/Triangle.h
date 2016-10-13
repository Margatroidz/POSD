#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Shape.h"

class Triangle : public Shape
{
public:
    Triangle(Point_t point1, Point_t point2, Point_t point3);
    ~Triangle();
    virtual double Area() const;
    virtual double Perimeter() const;
private:
    Point_t _point1;
    Point_t _point2;
    Point_t _point3;
};

#endif // TRIANGLE_H
