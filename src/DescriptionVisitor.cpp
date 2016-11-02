#include "Media.h"

DescriptionVisitor :: DescriptionVisitor()
{
    _descriptionStream.str("");
}

DescriptionVisitor :: ~DescriptionVisitor()
{
    //dtor
}

void DescriptionVisitor :: Visit(ShapeMedia* shapeMedia)
{
    _descriptionStream <<  shapeMedia->Description();
}

void DescriptionVisitor :: Visit(ComboMedia* comboMedia)
{
}

void DescriptionVisitor :: AddCombo()
{
    _descriptionStream << "combo(";
}

void DescriptionVisitor :: CompleteCombo()
{
    _descriptionStream << ")";
}

string DescriptionVisitor :: Description() const
{
    return _descriptionStream.str();
}
