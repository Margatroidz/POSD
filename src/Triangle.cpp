#include "Triangle.h"

double Triangle:: area()
{
    double line1 = sqrt(pow(abs(_point1.x - _point2.x), 2) + pow(abs(_point1.y - _point2.y), 2));
    double line2 = sqrt(pow(abs(_point2.x - _point3.x), 2) + pow(abs(_point2.y - _point3.y), 2));
    double line3 = sqrt(pow(abs(_point3.x - _point1.x), 2) + pow(abs(_point3.y - _point1.y), 2));
    double s = (line1 + line2 + line3) / 2;
    return sqrt(s * (s - line1) * (s - line2) *(s - line3));
}
double Triangle:: perimeter()
{
    double line1 = sqrt(pow(abs(_point1.x - _point2.x), 2) + pow(abs(_point1.y - _point2.y), 2));
    double line2 = sqrt(pow(abs(_point2.x - _point3.x), 2) + pow(abs(_point2.y - _point3.y), 2));
    double line3 = sqrt(pow(abs(_point3.x - _point1.x), 2) + pow(abs(_point3.y - _point1.y), 2));
    return line1 + line2 + line3;
}
