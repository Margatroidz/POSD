#include "Command.h"
#include "Media.h"
#include <string.h>
#include <cstdio>

struct RetrieveData
{
    char* def;
    MediaInfo* mediaInfo;
};

DeleteCommand :: DeleteCommand(const char* input, std::map<std::string, MediaInfo*> &container) : target(container), temp(nullptr), isRetrieve(false)
{
    excuteCommand = new char[512];
    unexcuteCommand = new char[512];

    strcpy(excuteCommand, input);
    if(strstr(input, " from "))
    {
        char* first = new char[256];
        char* second = new char[256];
        char* pch = new char[512];
        strcpy(pch, input);
        first = strtok(pch + 7, " ");
        strtok(NULL, " ");
        second = strtok(NULL, "\0");
        strcpy(unexcuteCommand, "add ");
        strcat(unexcuteCommand, first);
        strcat(unexcuteCommand, " to ");
        strcat(unexcuteCommand, second);
        delete[] first;
        delete[] second;
        delete[] pch;
    }
}

DeleteCommand :: ~DeleteCommand()
{
    delete[] excuteCommand;
    delete[] unexcuteCommand;

    if(!isRetrieve)
    {
        delete temp->media;
        delete[] temp->def;
        delete temp;
    }
}

void DeleteCommand :: Excute(bool output)
{
    Delete(excuteCommand, target);
    isRetrieve = false;
}

void DeleteCommand :: Unexcute()
{
    if(temp)
    {
        target.insert(std::make_pair(tempName, temp));
        for(RetrieveData* mi : retrieveData)
        {
            ((ComboMedia*)mi->mediaInfo->media)->Add(temp->media);
            strcpy(mi->mediaInfo->def, mi->def);
        }
    }
    else
    {
        Add(unexcuteCommand, target);
    }
    isRetrieve = true;
}

void DeleteCommand :: Delete(char* input, map<string, MediaInfo*> &container)
{
    const char* space = " ";
    char* pch = new char[512];
    strcpy(pch, input);
    pch = strtok(pch, space);

    pch = strtok(NULL, space);
    if(pch == NULL) throw("lack of parameter !");
    char deletedMedia[128];
    strcpy(deletedMedia, pch);

    pch = strtok(NULL, space);
    // !=NULL 代表後面還有接東西
    if(pch != NULL)
    {
        if(strncmp(pch, "from", 4) != 0) throw("illegal input !");
        pch = strtok(NULL, space);
        char deletedMediaContainer[128];
        strcpy(deletedMediaContainer, pch);

        map<string, MediaInfo*>::iterator itDM = container.find(deletedMedia);
        map<string, MediaInfo*>::iterator itDMC = container.find(deletedMediaContainer);
        if(itDM == container.end() || itDMC == container.end()) throw("variable cannot found !");
        Media* media = container[deletedMedia]->media;
        Media* combo = container[deletedMediaContainer]->media;
        combo->RemoveMedia(media);
        DeleteDef(container[deletedMediaContainer]->def, deletedMedia);
    }
    //後面沒接東西，先從map上刪掉，隻後再找每個combo，去移除有這個media的combo
    else
    {
        map<string, MediaInfo*>::iterator deletedIt = container.find(deletedMedia);

        if(deletedIt != container.end())
        {
            for(map<string, MediaInfo*>::iterator it = container.begin(); it != container.end(); ++it)
            {
                if(it->second->isCombo)
                {
                    it->second->media->RemoveMedia(deletedIt->second->media);
                    if(RetrieveData* rd = DeleteDef(it->second->def, deletedMedia)) rd->mediaInfo = it->second;
                }
            }
            tempName = deletedIt->first;
            temp = deletedIt->second;
            container.erase(deletedIt);
        }
    }
    delete[] pch;
}

void DeleteCommand :: Add(char* input, map<string, MediaInfo*> &container)
{
    const char* space = " ";
    char* pch = new char[512];
    strcpy(pch, input);
    strtok(pch, space);

    char* shape = strtok(NULL, space);
    if(shape == NULL) throw("lack of parameter !");
    if(strncmp(strtok(NULL, space), "to", 2) != 0) throw("illegal input !");
    char* combo = strtok(NULL, space);
    if(combo == NULL) throw("lack of parameter !");

    map<string, MediaInfo*>::iterator itS = container.find(shape);
    map<string, MediaInfo*>::iterator itC = container.find(combo);
    if(itS == container.end() || itC == container.end()) throw("variable cannot found !");
    if(!container[combo]->isCombo) throw("secondary variable is not a combo !");
    ((ComboMedia*)container[combo]->media)->Add(container[shape]->media);

    DescriptionVisitor dv;
    container[combo]->media->Accept(&dv);
    AddDef(container[combo]->def, shape);
    delete[] pch;
}

void DeleteCommand :: AddDef(char* def, char* target)
{
    char temp = def[strlen(def) - 1];
    char tempS[] = {' ', temp, '\0'};
    def[strlen(def) - 1] = '\0';
    strcat(def, target);
    strcat(def, tempS);
}

RetrieveData* DeleteCommand :: DeleteDef(char* def, char* target)
{
    char* defItr = def;
    int len = strlen(target);

    while(defItr != '\0')
    {
        if(strncmp(defItr, target, len) == 0) break;
        else defItr++;
    }

    len++;
    if(defItr != '\0')
    {
        RetrieveData* rd = new RetrieveData();
        char* predef = new char[256];
        strcpy(predef, def);
        rd->def = predef;
        while(*(defItr + len) != '\0')
        {
            *defItr = *(defItr + len);
            defItr++;
        }
        *defItr = '\0';
        return rd;
    }
    return nullptr;
}
