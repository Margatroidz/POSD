#include "Shape.h"

double PerimeterOfShapes(vector<Shape*> shapes)
{
    double sum = 0;
    for(Shape* s : shapes) sum += s->perimeter();
    return sum;
}

Shape* MaxArea(vector<Shape*> shapes)
{
    Shape* max = shapes[0];
    for(Shape* s : shapes) {
        if(s->area() > max->area()) max = s;
    }
    return max;
}

vector<Shape*> SortByDecreasingPerimeter(vector<Shape*> shapes)
{
    sort(shapes.begin(), shapes.end(), [](Shape* i, Shape* j) { return i->perimeter() > j->perimeter(); });
    return shapes;
}
