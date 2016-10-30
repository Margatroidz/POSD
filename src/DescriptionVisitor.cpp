#include "Media.h"

DescriptionVisitor :: DescriptionVisitor() :
    _description("")
{
    //ctor
}

DescriptionVisitor :: ~DescriptionVisitor()
{
    //dtor
}

void DescriptionVisitor :: Visit(ShapeMedia* shapeMedia)
{
    int remainComboSize = _remainCombo.size();
    _subDescription[remainComboSize - 1] = _subDescription[remainComboSize - 1] + shapeMedia->Description();
}

void DescriptionVisitor :: Visit(ComboMedia* comboMedia)
{
}

void DescriptionVisitor :: AddCombo(int amount)
{
    _description = _description + "combo(";
    _subDescription.push_back("");
    _remainCombo.push_back(amount);
}

void DescriptionVisitor :: CompleteCombo()
{
    _description = _description + _subDescription[_remainCombo.size() - 1] + ")";
    _remainCombo.pop_back();
    _subDescription.pop_back();
}

string DescriptionVisitor :: Description() const
{
    return _description;
}
