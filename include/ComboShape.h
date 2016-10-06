#ifndef COMBOSHAPE_H
#define COMBOSHAPE_H
#include "Shape.h"

class ComboShape : public Shape
{
public:
    ComboShape(Shape* s1, Shape* s2) { _shapes.push_back(s1);
                                       _shapes.push_back(s2); };
    ~ComboShape() {};
    virtual double Area() const ;
    virtual double Perimeter() const ;
    void Add(Shape* shape);
private:
    vector<Shape*> _shapes;
};

#endif // COMBOSHAPE_H
