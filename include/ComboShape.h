#ifndef COMBOSHAPE_H
#define COMBOSHAPE_H
#include "Shape.h"

class ComboShape : public Shape
{
public:
    ComboShape(string s) :
        _name(s) {};
    ~ComboShape() {};
    virtual double Area() const;
    virtual double Perimeter() const;
    void Add(Shape* shape);
private:
    string _name;
    vector<Shape*> _shapes;
};

#endif // COMBOSHAPE_H
