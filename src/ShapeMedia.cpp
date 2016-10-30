#include "Media.h"
#include <iostream>

ShapeMedia :: ShapeMedia(Shape* shape) :
    _shape(shape)
{
}

ShapeMedia :: ~ShapeMedia()
{
    delete _shape;
}

double ShapeMedia :: Area()
{
    return _shape->Area();
}

double ShapeMedia :: Perimeter()
{
    return _shape->Perimeter();
}

string ShapeMedia :: Description()
{
    return _shape->Description();
}

void ShapeMedia :: Accept(AreaVisitor* visitor)
{
    visitor->Visit(this);
}

void ShapeMedia :: Accept(PerimeterVisitor* visitor)
{
    visitor->Visit(this);
}

void ShapeMedia :: Accept(DescriptionVisitor* visitor)
{
    visitor->Visit(this);
}
