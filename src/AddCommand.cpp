#include "Command.h"
#include "Media.h"
#include <string.h>
#include <cstdio>

AddCommand :: AddCommand(const char* input, std::map<std::string, MediaInfo*> &container) : target(container)
{
    excuteCommand = new char[512];
    unexcuteCommand = new char[512];

    strcpy(excuteCommand, input);
    char* first = new char[256];
    char* second = new char[256];
    char* pch = new char[512];
    strcpy(pch, input);
    first = strtok(pch + 4, " ");
    strtok(NULL, " ");
    second = strtok(NULL, "\0");
    strcpy(unexcuteCommand, "delete ");
    strcat(unexcuteCommand, first);
    strcat(unexcuteCommand, " from ");
    strcat(unexcuteCommand, second);
    delete[] first;
    delete[] second;
    delete[] pch;
}

AddCommand :: ~AddCommand()
{
    delete[] excuteCommand;
    delete[] unexcuteCommand;
}

void AddCommand :: Excute(bool output)
{
    Add(excuteCommand, target, output);
}

void AddCommand :: Unexcute()
{
    Delete(unexcuteCommand, target);
}

void AddCommand :: Delete(char* input, map<string, MediaInfo*> &container)
{
    const char* space = " ";
    char* pch = strtok(input, space);

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
                    DeleteDef(it->second->def, deletedMedia);
                }
            }
            container.erase(deletedIt);
            delete deletedIt->second->media;
            delete[] deletedIt->second->def;
            delete deletedIt->second;
        }
    }
}

void AddCommand :: Add(char* input, map<string, MediaInfo*> &container, bool output)
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

    if(output) printf("   %s => %s = %s\n", combo, container[combo]->def, dv.Description().c_str());
}

void AddCommand :: AddDef(char* def, char* target)
{
    char temp = def[strlen(def) - 1];
    char tempS[] = {' ', temp, '\0'};
    def[strlen(def) - 1] = '\0';
    strcat(def, target);
    strcat(def, tempS);
}

void AddCommand :: DeleteDef(char* def, char* target)
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
        while(*(defItr + len) != '\0')
        {
            *defItr = *(defItr + len);
            defItr++;
        }
        *defItr = '\0';
    }
}
