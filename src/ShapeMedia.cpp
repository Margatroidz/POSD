#include "Media.h"

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

void ShapeMedia :: Accept(MediaVisitor* vistor)
{
    vistor->Visit(this);
}
