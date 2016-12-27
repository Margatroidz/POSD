#include "Command.h"
#include "Media.h"
#include <string.h>
#include <cstdio>
#include <iostream>

DefineCommand :: DefineCommand(const char* input, std::map<std::string, MediaInfo*> &container) : target(container), temp(nullptr)
{
    excuteCommand = new char[512];
    strcpy(excuteCommand, input);
}

DefineCommand :: ~DefineCommand()
{
    if(!isRetrieve)
    {
        delete[] temp->def;
        delete temp->media;
        delete temp;
    }
}

void DefineCommand :: Excute(bool output)
{
    if(!temp) ExtractShape(excuteCommand, 4, target);
    else target.insert(std::make_pair(tempName, temp));
    isRetrieve = true;
}

void DefineCommand :: Unexcute()
{
    isRetrieve = false;
    map<string, MediaInfo*>::iterator it = target.find(tempName);
    if(it != target.end()) target.erase(it);
}

void DefineCommand :: Delete(char* input, map<string, MediaInfo*> &container)
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

void DefineCommand :: ExtractShape(const char* input, int startPosition, map<string, MediaInfo*> &container)
{
    int position = startPosition;
    char name[128] = {0};
    char shape[512] = {0};

    //讀出shape名字
    while(input[position] != ' ')
    {
        if(input[position] == '\0') throw "illegal format !";
        name[position - startPosition] = input[position];
        position++;
    }
    name[position - startPosition] = '\0';
    if(container.find(string(name)) != container.end()) throw "variable has been declare !";

    if(!(input[position++] == ' ' && input[position++] == '=' && input[position++] == ' ')) throw "illegal format !";
    startPosition = position;

    //讀出shape的樣子
    while(input[position] != '\0')
    {
        shape[position - startPosition] = input[position];
        position++;
    }
    shape[position - startPosition] = '\0';


    bool isCombo;
    char* def = new char[128];
    strcpy(def, name);
    Media* m = CreateShape(shape, container, isCombo, def);
    MediaInfo* mi = new MediaInfo{m, isCombo, def};
    container.insert(std::make_pair(string(name), mi));
    temp = mi;
    tempName = string(name);
}

Media* DefineCommand :: CreateShape(char* input, map<string, MediaInfo*>& container, bool &isCombo, char* def)
{
    Media* result = nullptr;
    int inputPosition = 0;
    if(strncmp(input, "Circle", 6) == 0)
    {
        inputPosition = 6;
        isCombo = false;
        if(input[inputPosition] != '(') throw "illegal format !";
        float p1 = ReadFloat(input, ++inputPosition);
        if(input[inputPosition] != ',') throw "illegal format !";
        float p2 = ReadFloat(input, ++inputPosition);
        if(input[inputPosition] != ',') throw "illegal format !";
        float p3 = ReadFloat(input, ++inputPosition);
        if(input[inputPosition] != ')') throw "illegal format !";
        //真他媽智障，出題目的時候到底有沒有動腦想過啊 ?
        printf(">> Circle(%g,%g,%g)\n", p1, p2, p3);
        ShapeMediaBuilder sMB;
        sMB.BuildShapeMedia(new Circle(Point_t{p1, p2}, p3));
        result = sMB.GetMedia();
    }
    else if(strncmp(input, "Rectangle", 9) == 0)
    {
        inputPosition = 9;
        isCombo = false;
        if(input[inputPosition] != '(') throw "illegal format !";
        float p1 = ReadFloat(input, ++inputPosition);
        if(input[inputPosition] != ',') throw "illegal format !";
        float p2 = ReadFloat(input, ++inputPosition);
        if(input[inputPosition] != ',') throw "illegal format !";
        float p3 = ReadFloat(input, ++inputPosition);
        if(input[inputPosition] != ',') throw "illegal format !";
        float p4 = ReadFloat(input, ++inputPosition);
        if(input[inputPosition] != ')') throw "illegal format !";

        printf(">> Rectangle(%g,%g,%g,%g)\n", p1, p2, p3, p4);
        ShapeMediaBuilder sMB;
        sMB.BuildShapeMedia(new Rectangle(Point_t{p1, p2}, p3, p4));
        result = sMB.GetMedia();
    }
    else if(strncmp(input, "Triangle", 8) == 0)
    {
        inputPosition = 8;
        isCombo = false;
        if(input[inputPosition] != '(') throw "illegal format !";
        float p1 = ReadFloat(input, ++inputPosition);
        if(input[inputPosition] != ',') throw "illegal format !";
        float p2 = ReadFloat(input, ++inputPosition);
        if(input[inputPosition] != ',') throw "illegal format !";
        float p3 = ReadFloat(input, ++inputPosition);
        if(input[inputPosition] != ',') throw "illegal format !";
        float p4 = ReadFloat(input, ++inputPosition);
        if(input[inputPosition] != ',') throw "illegal format !";
        float p5 = ReadFloat(input, ++inputPosition);
        if(input[inputPosition] != ',') throw "illegal format !";
        float p6 = ReadFloat(input, ++inputPosition);
        if(input[inputPosition] != ')') throw "illegal format !";

        printf(">> Triangle(%g,%g,%g,%g,%g,%g)\n", p1, p2, p3, p4, p5, p6);
        ShapeMediaBuilder sMB;
        sMB.BuildShapeMedia(new Triangle(Point_t{p1, p2},Point_t{p3, p4},Point_t{p5, p6}));
        result = sMB.GetMedia();
    }
    else if(strncmp(input, "Combo", 5) == 0)
    {
        isCombo = true;
        char name[128];
        strcpy(name, def);
        result = CreateCombo(input, container, def);
        char shape[128];
        strcpy(shape, def);
        sprintf(def, "%s%s", name, shape);
        DefToSave(def);
    }
    else
    {
        throw "illegal format !";
    }

    return result;
}

Media* DefineCommand :: CreateCombo(char* input, map<string, MediaInfo*>& container, char* def)
{
    if(strncmp(input, "Combo", 5) != 0) throw "illegal format !";

    ComboMediaBuilder cMB;
    cMB.BuildComboMedia();

    string name;
    int inputPosition = 5;
    if(input[inputPosition] != '{') throw "illegal format !";

    while(true)
    {
        name = ReadString(input, ++inputPosition);
        map<string, MediaInfo*>::iterator it = container.find(name);

        if(it == container.end()) throw "variable cannot found !";
        cMB.BuildShapeMedia(container[name]->media);
        if(input[inputPosition] == '}') break;
        if(input[inputPosition] != ',') throw "illegal format !";
    }
    strcpy(def, input + strlen(name.c_str()) - 1);
    return cMB.GetMedia();
}

string DefineCommand :: ReadString(const char* input, int& position)
{
    char buffer[128] = {0};
    char* bufferPtr = buffer;
    while((input[position] >= 'A' && input[position] <= 'Z') || (input[position] >= 'a' && input[position] <= 'z'))
    {
        *bufferPtr = input[position];
        bufferPtr++;
        position++;
    }
    return string(buffer);
}

float DefineCommand :: ReadFloat(const char* input, int& position)
{
    char buffer[36] = {0};
    char* bufferPtr = buffer;
    int dotCount = 0;
    while((input[position] >= '0' && input[position] <= '9') || input[position] == '.')
    {
        if(input[position] == '.')
        {
            if(dotCount >= 1)throw "illegal format !";
            dotCount++;
        }
        *bufferPtr = input[position];
        bufferPtr++;
        position++;
    }
    return atof(buffer);
}

void DefineCommand :: DefToSave(char* def)
{
    int len = strlen(def);
    for(int i = 0; i < len; i ++) if(def[i] == ',') def[i] = ' ';

    def[len] = def[len - 1];
    def[len - 1] = ' ';
    def[len + 1] = '\0';
}

void DefineCommand :: DeleteDef(char* def, char* target)
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
