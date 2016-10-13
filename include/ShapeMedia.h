#ifndef SHAPEMEDIA_H
#define SHAPEMEDIA_H
#include "Media.h"
#include "Shape.h"

class ShapeMedia : Media
{
public:
    ShapeMedia(Shape* shape);
    virtual ~ShapeMedia();
private:
    Shape* _shape;
};

#endif // SHAPEMEDIA_H
