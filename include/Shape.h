#ifndef SHAPE_H
#define SHAPE_H
#define ERROR "Illegal input !"
#define PI 3.1415926
#include <algorithm>
#include <vector>
#include <string>
#include <math.h>
#include <stdlib.h>

using namespace std;

struct Point_t
{
    double x;
    double y;
};

class Shape
{
public:
    virtual ~Shape() {};
    virtual double Area() const = 0;
    virtual double Perimeter() const = 0;
};

double AreaOfShapes(const vector<Shape*> &shapes);

double PerimeterOfShapes(const vector<Shape*> &shapes);

Shape* MaxArea(vector<Shape*> &shapes);

vector<Shape*> SortByDecreasingPerimeter(vector<Shape*> shapes);

#endif // SHAPE_H
