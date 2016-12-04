#include "Media.h"

ShapeMediaBuilder :: ShapeMediaBuilder() : _shape(NULL)
{
}

ShapeMediaBuilder :: ~ShapeMediaBuilder()
{
}

void ShapeMediaBuilder :: BuildComboMedia()
{
    throw "can't build combo !";
}

void ShapeMediaBuilder :: BuildShapeMedia(Shape* s)
{
    _shape = new ShapeMedia(s);
}

Media* ShapeMediaBuilder :: GetMedia()
{
    return _shape;
}
