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
    _description += shapeMedia->Description();
    CompleteCombo(remainComboSize);
}

void DescriptionVisitor :: Visit(ComboMedia* comboMedia)
{
}

void DescriptionVisitor :: AddCombo(int amount)
{
    _description += "combo(";
    _remainCombo.push_back(amount);
}

void DescriptionVisitor :: CompleteCombo()
{
    int remainComboSize = _remainCombo.size();
    CompleteCombo(remainComboSize);
}

string DescriptionVisitor :: Description() const
{
    return _description;
}

void DescriptionVisitor :: CompleteCombo(int size)
{
    if(--_remainCombo[size - 1] == 0){
        _description += ")";
        _remainCombo.pop_back();
    }
}
