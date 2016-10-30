#include "Rectangle.h"
#include <sstream>

Rectangle :: Rectangle(Point_t upperLeft, double width, double height):
    _upperLeft(upperLeft), _width(width), _height(height)
{
    if(width < 0 || height < 0) throw ERROR;
}

Rectangle :: ~Rectangle()
{
};

double Rectangle :: Area() const
{
    return _width * _height;
}

double Rectangle :: Perimeter() const
{
    return 2 * (_width + _height);
}

string Rectangle :: Description() const
{
    stringstream ss;
    ss << "r(" << _upperLeft.x << " " << _upperLeft.y << " " << _width << " " << _height << ") ";
    return ss.str();
}
