#include "ShapeMedia.h"

ShapeMedia::ShapeMedia(Shape* shape) :
    _shape(shape)
{
}

ShapeMedia::~ShapeMedia()
{
    delete _shape;
}
