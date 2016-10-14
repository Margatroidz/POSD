#include "Media.h"

ComboMedia :: ComboMedia(Media* media1, Media* media2)
{
    _medias.push_back(media1);
    _medias.push_back(media2);
}

void ComboMedia :: Add(Media* m)
{
    _medias.push_back(m);
}

void ComboMedia :: Accept(MediaVisitor* vistor)
{
    for(Media* media : _medias)
        media->Accept(vistor);
}
