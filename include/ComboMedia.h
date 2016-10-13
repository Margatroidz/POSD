#ifndef COMBOMEDIA_H
#define COMBOMEDIA_H
#include <vector>
#include "Media.h"

using namespace std;

class ComboMedia : Media
{
public:
    ComboMedia();
    virtual ~ComboMedia();
    void Add(Media* media);
private:
    vector<Media*> _medias;
};

#endif // COMBOMEDIA_H
