#include "Media.h"

Media :: Media()
{
}

Media :: ~Media()
{
}

void Media :: Accept(MediaVisitor* vistor)
{
    throw "Prohibition Visitors";
}
