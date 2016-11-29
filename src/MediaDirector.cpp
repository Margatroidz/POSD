#include "Media.h"
#include <iostream>

void MediaDirector::setMediaBuilder(std::stack<ComboMediaBuilder *> *mbs)
{
}

Media* MediaDirector::GetMedia(){
    return media;
}

void MediaDirector::concrete(string content)
{
    const char* input = content.c_str();
    int position = -1;

    while(input[++position] != '\0')
    {
        switch(input[position])
        {
        //combo or circle
        case 'c':
            switch(input[++position])
            {
            case 'o':
            {
                if(input[++position] == 'm' && input[++position] == 'b' && input[++position] == 'o' && input[++position] == '(')
                {
                    mb->push(new ComboMediaBuilder());
                    mb->top()->BuildComboMedia();
                }
                else throw "error format";
            }
            break;
            case '(':
            {
                float p1 = ReadFloat(input, ++position);
                float p2 = ReadFloat(input, ++position);
                float p3 = ReadFloat(input, ++position);
                ShapeMediaBuilder* smb = new ShapeMediaBuilder();
                smb->BuildShapeMedia(new Circle(Point_t{p1, p2}, p3));
                if(mb->size() == 0){
                    media = smb->GetMedia();
                    return;
                }
                mb->top()->BuildShapeMedia(smb->GetMedia());
            }
            break;
            }
            break;
        //rectangle
        case 'r':
            if(input[++position] == '(')
            {
                float p1 = ReadFloat(input, ++position);
                float p2 = ReadFloat(input, ++position);
                float p3 = ReadFloat(input, ++position);
                float p4 = ReadFloat(input, ++position);
                ShapeMediaBuilder* smb = new ShapeMediaBuilder();
                smb->BuildShapeMedia(new Rectangle(Point_t{p1, p2}, p3, p4));
                if(mb->size() == 0){
                    media = smb->GetMedia();
                    return;
                }
                mb->top()->BuildShapeMedia(smb->GetMedia());
            }
            break;
        //triangle
        case 't':
            if(input[++position] == '(')
            {
                float p1 = ReadFloat(input, ++position);
                float p2 = ReadFloat(input, ++position);
                float p3 = ReadFloat(input, ++position);
                float p4 = ReadFloat(input, ++position);
                float p5 = ReadFloat(input, ++position);
                float p6 = ReadFloat(input, ++position);
                ShapeMediaBuilder* smb = new ShapeMediaBuilder();
                smb->BuildShapeMedia(new Triangle(Point_t{p1, p2}, Point_t{p3, p4}, Point_t{p5, p6}));
                if(mb->size() == 0){
                    media = smb->GetMedia();
                    return;
                }
                mb->top()->BuildShapeMedia(smb->GetMedia());
            }
            break;
        //comboEnd
        case ')':
            if(!mb->empty())
            {
                if(mb->size() > 1)
                {
                    ComboMediaBuilder* cm = mb->top();
                    mb->pop();
                    mb->top()->BuildShapeMedia(cm->GetMedia());
                }
            }
            else throw "error format";
            break;
        }
    }
    media = mb->top()->GetMedia();
}

float MediaDirector::ReadFloat(const char* input, int& position)
{
    char buffer[36] = {0};
    char* bufferPtr = buffer;
    while((input[position] >= '0' && input[position] <= '9') || input[position] == '.')
    {
        *bufferPtr = input[position];
        bufferPtr++;
        position++;
    }
    if(input[position] != ' ' && input[position] != ')') throw "error format";
    return atof(buffer);
}
