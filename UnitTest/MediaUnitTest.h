#ifndef UNITTEST_H_INCLUDED
#define UNITTEST_H_INCLUDED
#include "Media.h"
#include "Shapes.h"
#include <vector>
#include <string.h>
#define THRESH_HLOD 0.00001
#include "iostream"
TEST(ComboMediaTest, RegularHexagon)
{
    double SqrtThree = 1.7320508;
    Point_t t11 = {0.0, 0.0};
    Point_t t12 = {SqrtThree * 2, 0.0};
    Point_t t13 = {SqrtThree, 1.0};
    Point_t t21 = {0.0, -2.0};
    Point_t t22 = {SqrtThree * 2, -2.0};
    Point_t t23 = {SqrtThree, -3.0};

    Media* r = new ShapeMedia(new Rectangle(t11, SqrtThree * 2, 2));
    Media* t1 = new ShapeMedia(new Triangle(t11, t12, t13));
    Media* t2 = new ShapeMedia(new Triangle(t21, t22, t23));

    ComboMedia* cm = new ComboMedia(r, t1);
    cm->Add(t2);

    try
    {
        AreaVisitor* av = new AreaVisitor();
        cm->Accept(av);
        std::cout << av->TotalArea() << endl;
    }
    catch(string e)
    {
        std::cout << e << endl;
    }
}

#endif // UNITTEST_H_INCLUDED
