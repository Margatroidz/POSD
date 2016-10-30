#include "Media.h"

PerimeterVisitor :: PerimeterVisitor() :
    _total(0)
{
    //ctor
}

PerimeterVisitor :: ~PerimeterVisitor()
{
    //dtor
}

void PerimeterVisitor :: Visit(ShapeMedia* shapeMedia)
{
    _total += shapeMedia->Perimeter();
}

void PerimeterVisitor :: Visit(ComboMedia* comboMedia)
{
}

double PerimeterVisitor :: TotalPerimeter() const
{
    return _total;
}
