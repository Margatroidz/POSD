#ifndef SHAPE_H
#define SHAPE_H
#define ERROR "Illegal input !"
#define PI 3.1415926
#include <list>
#include <vector>
#include <math.h>
#include <stdlib.h>

struct Point_t
{
    double x;
    double y;
};

class Shape
{
public:
    virtual ~Shape() {};
    virtual double area() = 0;
    virtual double perimeter() = 0;
};

double PerimeterOfShapes(std::vector<Shape*> shapes);

Shape* MaxArea(std::vector<Shape*> shapes);

std::vector<Shape*> SortByDecreasingPerimeter(std::vector<Shape*> shapes);

#endif // SHAPE_H
