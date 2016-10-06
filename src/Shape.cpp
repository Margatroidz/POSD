#include "Shape.h"

double AreaOfShapes(vector<Shape*> shapes)
{
    double sum = 0;
    for(Shape* s : shapes) sum += s->Area();
    return sum;
}

double PerimeterOfShapes(vector<Shape*> shapes)
{
    double sum = 0;
    for(Shape* s : shapes) sum += s->Perimeter();
    return sum;
}

Shape* MaxArea(vector<Shape*> shapes)
{
    Shape* max = shapes[0];
    for(Shape* s : shapes) {
        if(s->Area() > max->Area()) max = s;
    }
    return max;
}

vector<Shape*> SortByDecreasingPerimeter(vector<Shape*> shapes)
{
    sort(shapes.begin(), shapes.end(), [](Shape* i, Shape* j) { return i->Perimeter() > j->Perimeter(); });
    return shapes;
}
