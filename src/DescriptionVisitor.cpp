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
    int remainComboSize = _remainCombo.size();
    _descriptionStream <<  shapeMedia->Description();
    CompleteCombo(remainComboSize);
}

void DescriptionVisitor :: Visit(ComboMedia* comboMedia)
{
}

void DescriptionVisitor :: AddCombo(int amount)
{
    _descriptionStream << "combo(";
    _remainCombo.push_back(amount);
}

void DescriptionVisitor :: CompleteCombo()
{
    int remainComboSize = _remainCombo.size();
    CompleteCombo(remainComboSize);
}

string DescriptionVisitor :: Description() const
{
    return _descriptionStream.str();
}

void DescriptionVisitor :: CompleteCombo(int size)
{
    if(--_remainCombo[size - 1] == 0){
        _descriptionStream << ")";
        _remainCombo.pop_back();
    }
}
