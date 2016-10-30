#include "Media.h"

AreaVisitor :: AreaVisitor() :
    _total(0)
{
    //ctor
}

AreaVisitor :: ~AreaVisitor()
{
    //dtor
}

void AreaVisitor :: Visit(ShapeMedia* shapeMedia)
{
    _total += shapeMedia->Area();
}

void AreaVisitor :: Visit(ComboMedia* comboMedia)
{
}

double AreaVisitor :: TotalArea() const
{
    return _total;
}
