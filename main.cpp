#include <iostream>
#include "cppunitlite/TestHarness.h"
#include "UnitTest/MediaUnitTest.h"
#include "UnitTest/ShapeUnitTest.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <map>

using namespace std;

struct MediaInfo
{
    Media* media;
    bool isCombo;
    char* def;
};

void Save(char* input, map<string, MediaInfo*> &container);
void Load(char* input, map<string, MediaInfo*> &container);
void Add(char* input, map<string, MediaInfo*> &container);
void Delete(char* input, map<string, MediaInfo*> &container);
void Calculate(char* input, map<string, MediaInfo*> &container);

void ExtractShape(const char* input, int startPosition, map<string, MediaInfo*> &container);
Media* CreateShape(char* input, map<string, MediaInfo*> &container, bool &isCombo, char* def);
Media* CreateCombo(char* input, map<string, MediaInfo*> &container, char* def);
float ReadFloat(const char* input, int& position);
string ReadString(const char* input, int& position);
void DefToSave(char* def);
void LoadToDef(char* def, int &startPosition);
void DeleteDef(char* def, char* target);
void AddDef(char* def, char* target);

//media命名自行避開關鍵字，否則部分操作會異常
int main()
{
    TestResult testResult;
    TestRegistry::runAllTests(testResult);
    map<string, MediaInfo*> shapeContainer;

    while(true)
    {
        char input[512] = "";
        char dump;
        printf(":- ");
        scanf("%[^\n]", &input);
        scanf("%c", &dump);

        try
        {
            if(input[0] == '\0') printf("   please enter some word !\n");
            else if(strncmp(input, "def ", 4) == 0)
            {
                ExtractShape(input, 4, shapeContainer);
            }
            else if(strncmp(input, "save", 4) == 0)
            {
                Save(input, shapeContainer);
            }
            else if(strncmp(input, "load", 4) == 0)
            {
                Load(input, shapeContainer);
            }
            else if(strncmp(input, "add", 3) == 0)
            {
                Add(input, shapeContainer);
            }
            else if(strncmp(input, "show", 4) == 0)
            {
                for(map<string, MediaInfo*>::iterator it = shapeContainer.begin() ; it != shapeContainer.end() ; ++it)
                    printf("   %s\n", it->first.c_str());
            }
            else if(strncmp(input, "delete", 4) == 0)
            {
                Delete(input, shapeContainer);
            }
            else if(strncmp(input, "exit", 4) == 0)
            {
                break;
            }
            else
            {
                Calculate(input, shapeContainer);
            }
        }
        catch(const char* ex)
        {
            printf("   %s\n", ex);
        }
    }
    printf("\n");
    for(map<string, MediaInfo*>::iterator it = shapeContainer.begin() ; it != shapeContainer.end() ; ++it)
    {
        delete it->second->media;
        delete[] it->second->def;
        delete it->second;
    }
}

void Save(char* input, map<string, MediaInfo*> &container)
{
    const char* space = " ";
    const char* quotes = "\"";
    char* pch = strtok(input, space);

    pch = strtok(NULL, space);
    if(container.find(pch) == container.end()) throw "illegal shape !";
    if(!container.find(pch)->second->isCombo) throw "have to be a combo !";
    MediaInfo* mi = container[pch];

    pch = strtok(NULL, space);
    if(strncmp(pch, "to", 2) != 0) throw "illegal file name !";

    pch = strtok(NULL, quotes);
    if(pch == NULL || *pch == '\0') throw "illegal file name !";

    fstream file(pch, ifstream::out);
    DescriptionVisitor dv;
    mi->media->Accept(&dv);
    file << dv.Description() << endl;
    file << mi->def << endl;
    file.close();
}
void Load(char* input, map<string, MediaInfo*> &container)
{
    for(map<string, MediaInfo*>::iterator it = container.begin() ; it != container.end() ;)
    {
        char* temp = new char[256];
        strcpy(temp, ("delete " + (it++)->first).c_str());
        Delete(temp, container);
        delete[] temp;
    }

    const char* space = " ";
    const char* quotes = "\"";
    char* pch = strtok(input, quotes);
    pch = strtok(NULL, quotes);
    string buffer;
    char* line1 = new char[512];
    char* line2 = new char[512];
    char* shape = new char[512];
    char* name = new char[512];
    char* temp = new char[512];
    char* temp2 = new char[512];
    fstream file(pch, ifstream::in);
    if(!file.is_open()) throw "file can't not found !";

    getline(file, buffer);
    strcpy(line1, buffer.c_str());
    getline(file, buffer);
    strcpy(line2, buffer.c_str());
    if(getline(file, buffer)) throw "illegal format !";
    file.close();

    int defPosition = 6;
    int len = strlen(line1) - 1;
    while(defPosition < len)
    {
        LoadToDef(line1, defPosition);
        defPosition += 2;
    }

    pch = strtok(line1 + 6, space);
    int namePosition = 0;
    strcpy(temp, ReadString(line2, namePosition).c_str());
    strcpy(temp2, line2 + namePosition);

    while(strncmp((line2++) + namePosition, " }", 2) != 0)
    {
        strcpy(name, ReadString(line2, namePosition).c_str());
        switch(pch[0])
        {
        case 'c':
            strcpy(shape, "Circle");
            break;
        case 't':
            strcpy(shape, "Triangle");
            break;
        case 'r':
            strcpy(shape, "Rectangle");
            break;
        }
        strcat(shape, pch + 1);
        string comment = "def " + string(name) + " = " + string(shape);
        pch = strtok(NULL, space);
        ExtractShape(comment.c_str(), 4, container);
    }
    int tempPosition = 0;
    LoadToDef(temp2, tempPosition);
    string comment = "def " + string(temp) + " = Combo" + string(temp2);
    ExtractShape(comment.c_str(), 4, container);

    delete[] line1;
    delete[] line2;
    delete[] shape;
    delete[] name;
    delete[] temp;
    delete[] temp2;
}

void Add(char* input, map<string, MediaInfo*> &container)
{
    const char* space = " ";
    strtok(input, space);

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

    printf("   %s => %s = %s\n", combo, container[combo]->def, dv.Description().c_str());
}

void Delete(char* input, map<string, MediaInfo*> &container)
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
void Calculate(char* input, map<string, MediaInfo*> &container)
{
    const char* dot = ".";
    char* pchName = strtok(input, dot);

    map<string, MediaInfo*>::iterator it = container.find(pchName);
    char* pchOperation = strtok(NULL, dot);

    if(pchOperation == NULL) throw("comment cannot found !");
    if(it == container.end()) throw("variable cannot found !");
    Media* media = container[pchName]->media;

    char operation[128];
    strcpy(operation, pchOperation);
    if(strtok(NULL, dot) != NULL) throw("illegal input !");
    if(strncmp(operation, "area?", 5) == 0)
    {
        AreaVisitor av;
        media->Accept(&av);
        printf(">> %g\n", av.TotalArea());
    }
    else if(strncmp(operation, "perimeter?", 10) == 0)
    {
        PerimeterVisitor pv;
        media->Accept(&pv);
        printf(">> %g\n", pv.TotalPerimeter());
    }
    else
    {
        throw("illegal operation !");
    }
}

void ExtractShape(const char* input, int startPosition, map<string, MediaInfo*> &container)
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
}

Media* CreateShape(char* input, map<string, MediaInfo*>& container, bool &isCombo, char* def)
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

Media* CreateCombo(char* input, map<string, MediaInfo*>& container, char* def)
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

float ReadFloat(const char* input, int& position)
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

string ReadString(const char* input, int& position)
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

void DefToSave(char* def)
{
    int len = strlen(def);
    for(int i = 0; i < len; i ++) if(def[i] == ',') def[i] = ' ';

    def[len] = def[len - 1];
    def[len - 1] = ' ';
    def[len + 1] = '\0';
}

void LoadToDef(char* def, int &startPosition)
{
    int len = strlen(def);
    for(; startPosition < len; startPosition ++)
    {
        if(def[startPosition] == ')' || def[startPosition] == '}') break;
        if(def[startPosition] == ' ') def[startPosition] = ',';
    }
    if(def[startPosition - 1] == ',')
    {
        def[startPosition - 1] = def[startPosition];
        def[startPosition] = '\0';
    }
}

void DeleteDef(char* def, char* target)
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
void AddDef(char* def, char* target)
{
    char temp = def[strlen(def) - 1];
    char tempS[] = {' ', temp, '\0'};
    def[strlen(def) - 1] = '\0';
    strcat(def, target);
    strcat(def, tempS);
}
