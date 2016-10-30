#include "Triangle.h"
#include <sstream>

Triangle :: Triangle(Point_t point1, Point_t point2, Point_t point3):
    _point1(point1), _point2(point2), _point3(point3)
{
    double line1 = sqrt(pow(abs(point1.x - point2.x), 2) + pow(abs(point1.y - point2.y), 2));
    double line2 = sqrt(pow(abs(point2.x - point3.x), 2) + pow(abs(point2.y - point3.y), 2));
    double line3 = sqrt(pow(abs(point3.x - point1.x), 2) + pow(abs(point3.y - point1.y), 2));
    if((line1 + line2 <= line3) || (line1 + line3 <= line2) || (line2 + line3 <= line1)) throw ERROR;
}

Triangle :: ~Triangle()
{
};

double Triangle :: Area() const
{
    double line1 = sqrt(pow(abs(_point1.x - _point2.x), 2) + pow(abs(_point1.y - _point2.y), 2));
    double line2 = sqrt(pow(abs(_point2.x - _point3.x), 2) + pow(abs(_point2.y - _point3.y), 2));
    double line3 = sqrt(pow(abs(_point3.x - _point1.x), 2) + pow(abs(_point3.y - _point1.y), 2));
    double s = (line1 + line2 + line3) / 2;
    return sqrt(s * (s - line1) * (s - line2) *(s - line3));
}
double Triangle :: Perimeter() const
{
    double line1 = sqrt(pow(abs(_point1.x - _point2.x), 2) + pow(abs(_point1.y - _point2.y), 2));
    double line2 = sqrt(pow(abs(_point2.x - _point3.x), 2) + pow(abs(_point2.y - _point3.y), 2));
    double line3 = sqrt(pow(abs(_point3.x - _point1.x), 2) + pow(abs(_point3.y - _point1.y), 2));
    return line1 + line2 + line3;
}

string Triangle :: Description() const
{
    stringstream ss;
    ss << "t(" << _point1.x << " " << _point1.y << " " << _point2.x << " " << _point2.y << " " << _point3.x << " " << _point3.y << ") ";
    return ss.str();
}
