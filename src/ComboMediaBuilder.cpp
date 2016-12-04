#include "Media.h"

ComboMediaBuilder :: ComboMediaBuilder() : _combo(NULL)
{

}

ComboMediaBuilder :: ~ComboMediaBuilder()
{
}

void ComboMediaBuilder :: BuildComboMedia()
{
    _combo = new ComboMedia();
}

void ComboMediaBuilder :: BuildShapeMedia(Shape* s)
{
    if(_combo == NULL) throw "need a combo !";
    _shapesTemp.push_back(new ShapeMedia(s));
    _combo->Add(_shapesTemp[_shapesTemp.size() - 1]);
}

void ComboMediaBuilder :: BuildShapeMedia(Media* media)
{
    if(_combo == NULL) throw "need a combo !";
    _shapesTemp.push_back(media);
    _combo->Add(media);
}

void ComboMediaBuilder :: RemoveMedia(Media* media)
{
    if(_combo == NULL) throw "need a combo !";
    _combo->RemoveMedia(media);
}

Media* ComboMediaBuilder :: GetMedia()
{
    return _combo;
}
