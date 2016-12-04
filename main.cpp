#include <iostream>
#include "cppunitlite/TestHarness.h"
#include "UnitTest/MediaUnitTest.h"
#include "UnitTest/ShapeUnitTest.h"
#include <stdio.h>
#include <stdlib.h>
#include <map>

using namespace std;

void Save();
void Load();
void Delete(char* input, map<string, Media*> &container);
void Calculate(char* input, map<string, Media*> &container);

void ExtractShape(char* input, int startPosition, map<string, Media*> &container);
Media* CreateShape(char* input, map<string, Media*> &container);
Media* CreateCombo(char* input, map<string, Media*> &container);
float ReadFloat(const char* input, int& position);
string ReadString(const char* input, int& position);

//media命名自行避開關鍵字，否則部分操作會異常
int main()
{
    TestResult testResult;
    TestRegistry::runAllTests(testResult);
    map<string, Media*> shapeContainer;

    while(true)
    {
        char input[512] = "";
        char dump;
        printf(":- ");
        scanf("%[^\n]", &input);
        scanf("%c", &dump);

        if(strncmp(input, "def ", 4) == 0)
        {
            try
            {
                ExtractShape(input, 4, shapeContainer);
            }
            catch( ... )
            {
                printf("   illegal input !\n");
            }
        }
        else if(strncmp(input, "save", 4) == 0)
        {
        }
        else if(strncmp(input, "load", 4) == 0)
        {
        }
        else if(strncmp(input, "show", 4) == 0)
        {
            for(map<string, Media*>::iterator it = shapeContainer.begin() ; it != shapeContainer.end() ; ++it)
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
    printf("\n");
}

void Save()
{

}
void Load()
{

}
void Delete(char* input, map<string, Media*> &container)
{
    const char* space = " ";
    char* pch = strtok(input, space);

    pch = strtok(NULL, space);
    string deletedMedia = string(pch);

    pch = strtok(NULL, space);
    // !=NULL 代表後面還有接東西
    if(pch != NULL)
    {
        if(strncmp(pch, "from", 4) != 0) printf("   illegal input !\n");
        else
        {
            string deletedMediaContainer = string(pch);

            map<string, Media*>::iterator itDM = container.find(deletedMedia);
            map<string, Media*>::iterator itDMC = container.find(deletedMediaContainer);

            if(itDM != container.end() && itDMC != container.end())
            {
                Media* media = container[deletedMedia];
                Media* combo = container[deletedMediaContainer];
                combo->RemoveMedia(media);
            }
            else
            {
                printf("   variable cannot found\n");
            }
        }
    }
    //後面沒接東西，直接刪
    else
    {
        map<string, Media*>::iterator it = container.find(deletedMedia);
        if(it != container.end()) container.erase(it);
    }
}
void Calculate(char* input, map<string, Media*> &container)
{
    const char* dot = ".";
    char* pch = strtok(input, dot);

    map<string, Media*>::iterator it = container.find(pch);

    if(it != container.end())
    {
        Media* media = container[string(pch)];
        pch = strtok(NULL, dot);
        char operation[128];
        strcpy(operation, pch);
        if(strtok(NULL, dot) != NULL) printf("   illegal input !\n");
        else
        {
            if(strncmp(operation, "area?", 5) == 0)
            {
                AreaVisitor av;
                media->Accept(&av);
                printf("   %g\n", av.TotalArea());
            }
            else if(strncmp(operation, "perimeter?", 10) == 0)
            {
                PerimeterVisitor pv;
                media->Accept(&pv);
                printf("   %g\n", pv.TotalPerimeter());
            }
            else
            {
                printf("   illegal operation\n");
            }
        }
    }
    else
    {
        printf("   variable cannot found\n");
    }
}

void ExtractShape(char* input, int startPosition, map<string, Media*> &container)
{
    int position = startPosition;
    char name[128] = {0};
    char shape[512] = {0};

    //讀出shape名字
    while(input[position] != ' ')
    {
        if(input[position] == '\0') throw string("error");
        name[position - startPosition] = input[position];
        position++;
    }
    name[position - startPosition] = '\0';

    if(!(input[position++] == ' ' && input[position++] == '=' && input[position++] == ' ')) throw string("error");
    startPosition = position;

    //讀出shape的樣子
    while(input[position] != '\0')
    {
        shape[position - startPosition] = input[position];
        position++;
    }
    shape[position - startPosition] = '\0';

    Media* result = CreateShape(shape, container);
    container.insert(std::make_pair(string(name), result));
}

Media* CreateShape(char* input, map<string, Media*>& container)
{
    Media* result = nullptr;
    int inputPosition = 0;
    if(strncmp(input, "Circle", 6) == 0)
    {
        inputPosition = 6;
        if(input[inputPosition] != '(') throw "error";
        float p1 = ReadFloat(input, ++inputPosition);
        if(input[inputPosition] != ',') throw "error";
        float p2 = ReadFloat(input, ++inputPosition);
        if(input[inputPosition] != ',') throw "error";
        float p3 = ReadFloat(input, ++inputPosition);
        if(input[inputPosition] != ')') throw "error";

        printf("   Circle(%g,%g,%g)\n", p1, p2, p3);
        ShapeMediaBuilder sMB;
        sMB.BuildShapeMedia(new Circle(Point_t{p1, p2}, p3));
        result = sMB.GetMedia();
    }
    else if(strncmp(input, "Rectangle", 9) == 0)
    {
        inputPosition = 9;
        if(input[inputPosition] != '(') throw "error";
        float p1 = ReadFloat(input, ++inputPosition);
        if(input[inputPosition] != ',') throw "error";
        float p2 = ReadFloat(input, ++inputPosition);
        if(input[inputPosition] != ',') throw "error";
        float p3 = ReadFloat(input, ++inputPosition);
        if(input[inputPosition] != ',') throw "error";
        float p4 = ReadFloat(input, ++inputPosition);
        if(input[inputPosition] != ')') throw "error";

        printf("   Rectangle(%g,%g,%g,%g)\n", p1, p2, p3, p4);
        ShapeMediaBuilder sMB;
        sMB.BuildShapeMedia(new Rectangle(Point_t{p1, p2}, p3, p4));
        result = sMB.GetMedia();
    }
    else if(strncmp(input, "Triangle", 8) == 0)
    {
        inputPosition = 8;
        if(input[inputPosition] != '(') throw "error";
        float p1 = ReadFloat(input, ++inputPosition);
        if(input[inputPosition] != ',') throw "error";
        float p2 = ReadFloat(input, ++inputPosition);
        if(input[inputPosition] != ',') throw "error";
        float p3 = ReadFloat(input, ++inputPosition);
        if(input[inputPosition] != ',') throw "error";
        float p4 = ReadFloat(input, ++inputPosition);
        if(input[inputPosition] != ',') throw "error";
        float p5 = ReadFloat(input, ++inputPosition);
        if(input[inputPosition] != ',') throw "error";
        float p6 = ReadFloat(input, ++inputPosition);
        if(input[inputPosition] != ')') throw "error";

        printf("   Triangle(%g,%g,%g,%g,%g,%g)\n", p1, p2, p3, p4, p5, p6);
        ShapeMediaBuilder sMB;
        sMB.BuildShapeMedia(new Triangle(Point_t{p1, p2},Point_t{p3, p4},Point_t{p5, p6}));
        result = sMB.GetMedia();
    }
    else if(strncmp(input, "Combo", 5) == 0)
    {
        result = CreateCombo(input, container);
    }
    else
    {
        throw "error shape";
    }

    return result;
}

Media* CreateCombo(char* input, map<string, Media*>& container)
{
    if(strncmp(input, "Combo", 5) == 0)
    {
        ComboMediaBuilder cMB;
        cMB.BuildComboMedia();

        string name;
        int inputPosition = 5;
        if(input[inputPosition] != '{') throw "error";

        while(true)
        {
            name = ReadString(input, ++inputPosition);
            map<string, Media*>::iterator it = container.find(name);

            if(it != container.end())
            {
                cMB.BuildShapeMedia(container[name]);
                if(input[inputPosition] == '}') break;
                if(input[inputPosition] != ',') throw "error format";
            }
            else
            {
                throw "variable cannot found";
            }
        }

        return cMB.GetMedia();
    }
    else
    {
        throw "error combo";
    }
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
            if(dotCount >= 1)throw "error format";
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

