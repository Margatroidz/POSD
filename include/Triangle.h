#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Shape.h"

class Triangle : public Shape
{
public:
    Triangle(Point_t point1, Point_t point2, Point_t point3):
        _point1(point1), _point2(point2), _point3(point3) { double line1 = sqrt(pow(abs(point1.x - point2.x), 2) + pow(abs(point1.y - point2.y), 2));
                                                            double line2 = sqrt(pow(abs(point2.x - point3.x), 2) + pow(abs(point2.y - point3.y), 2));
                                                            double line3 = sqrt(pow(abs(point3.x - point1.x), 2) + pow(abs(point3.y - point1.y), 2));
                                                            if((line1 + line2 <= line3) || (line1 + line3 <= line2) || (line2 + line3 <= line1)) throw ERROR;};
    ~Triangle() {};
    virtual double area();
    virtual double perimeter();
private:
    Point_t _point1;
    Point_t _point2;
    Point_t _point3;
};

#endif // TRIANGLE_H
