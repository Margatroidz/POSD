#include "Shape.h"

using namespace std;

inline void Swap(Shape* s1, Shape* s2){
    Shape* temp = s1;
    s1 = s2;
    s2 = temp;
}

double PerimeterOfShapes(vector<Shape*> shapes)
{
    double sum = 0;
    for(Shape* s : shapes) sum += s->perimeter();
    return sum;
}

Shape* MaxArea(std::vector<Shape*> shapes)
{
    Shape* max = shapes[0];
    for(Shape* s : shapes) {
        if(s->area() > max->area()) max = s;
    }
    return max;
}

std::vector<Shape*> SortByDecreasingPerimeter(std::vector<Shape*> shapes)
{
    list<Shape*>::iterator it;
    list<Shape*> tempList;
    vector<Shape*> result;

    for(Shape* s : shapes){
        for(it = tempList.begin(); it != tempList.end(); it++) {
            if(s->perimeter() >= (*it)->perimeter()){
                tempList.insert(it, s);
                break;
            }
        }
        if(it == tempList.end()) tempList.push_back(s);
    }

    for (Shape* st : tempList) result.push_back(st);
    return result;
}
