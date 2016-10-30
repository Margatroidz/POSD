#include "Media.h"

#include "Media.h"

TextMedia :: TextMedia(Rectangle* rectangle, string text) : _rectangle(rectangle), _text(text)
{
}

TextMedia :: ~TextMedia()
{
    delete _rectangle;
}

void TextMedia :: Accept(AreaVisitor* visitor)
{
}

void TextMedia :: Accept(PerimeterVisitor* visitor)
{
}

void TextMedia :: Accept(DescriptionVisitor* visitor)
{
}

string TextMedia :: Text()
{
    return _text;
}
