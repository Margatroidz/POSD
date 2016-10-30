#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Shape.h"

class Rectangle : public Shape
{
public:
    Rectangle(Point_t upperLeft, double width, double height);
    ~Rectangle();
    virtual double Area() const;
    virtual double Perimeter() const;
    virtual string Description() const;
private:
    Point_t _upperLeft;
    double _width;
    double _height;
};

#endif // RECTANGLE_H
