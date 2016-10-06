#include "ComboShape.h"

void ComboShape::Add(Shape* s){
     _shapes.push_back(s);
}

double ComboShape::Area() const {
    return AreaOfShapes(_shapes);
}

double ComboShape::Perimeter() const {
    return PerimeterOfShapes(_shapes);
}
