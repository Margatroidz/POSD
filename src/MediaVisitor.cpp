#include "Media.h"

MediaVisitor :: MediaVisitor()
{
    //ctor
}

MediaVisitor :: ~MediaVisitor()
{
    //dtor
}

void MediaVisitor :: Visit(ShapeMedia* shapeMedia)
{
    throw "Prohibition Visitors";
}
void MediaVisitor :: Visit(ComboMedia* comboMedia)
{
    throw "Prohibition Visitors";
}
