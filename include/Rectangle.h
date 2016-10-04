#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Shape.h"

class Rectangle : public Shape
{
public:
    Rectangle(Point_t upperLeft, double width, double height):
        _upperLeft(upperLeft), _width(width), _height(height) { if(width < 0 || height < 0) throw ERROR; };
    ~Rectangle() {};
    virtual double area();
    virtual double perimeter();
private:
    Point_t _upperLeft;
    double _width;
    double _height;
};

#endif // RECTANGLE_H
