#ifndef COMBOSHAPE_H
#define COMBOSHAPE_H
#include "Shape.h"

class ComboShape : public Shape
{
public:
    ComboShape(string s) :
        _name(s) {};
    ~ComboShape() {};
    virtual double area();
    virtual double perimeter();
    //void Add(Shape* shape);
private:
    string _name;
};

#endif // COMBOSHAPE_H
