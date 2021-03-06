#include "Media.h"

ComboMedia :: ComboMedia()
{
}

ComboMedia :: ComboMedia(Media* media1, Media* media2)
{
    _medias.push_back(media1);
    _medias.push_back(media2);
}

void ComboMedia :: Add(Media* media)
{
    _medias.push_back(media);
}

void ComboMedia :: Accept(AreaVisitor* visitor)
{
    for(Media* media : _medias)
        media->Accept(visitor);
}

void ComboMedia :: Accept(PerimeterVisitor* visitor)
{
    for(Media* media : _medias)
        media->Accept(visitor);
}

void ComboMedia :: Accept(DescriptionVisitor* visitor)
{
    visitor->AddCombo();
    for(Media* media : _medias)
        media->Accept(visitor);
    visitor->CompleteCombo();
}

void ComboMedia :: RemoveMedia(Media* media)
{
    for(vector<Media*>::iterator it = _medias.begin(); it != _medias.end(); it++){
        if(*it == media) {
            _medias.erase(it);
            return;
        }
        (*it)->RemoveMedia(media);
    }
}
