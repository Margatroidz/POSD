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

void ComboMedia :: RemoveMedia(Media* media)
{
    for(vector<Media*>::iterator it = _medias.begin(); it != _medias.end(); it++){
        if(*it == media) {
            _medias.erase(it);
            return;
        }
    }
    throw "media that want to remove doesn't in this comboMedia";
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
    visitor->AddCombo(_medias.size());
    for(Media* media : _medias)
        media->Accept(visitor);
    visitor->CompleteCombo();
}
