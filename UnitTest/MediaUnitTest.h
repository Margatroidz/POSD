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

    AreaVisitor* av = new AreaVisitor();
    cm->Accept(av);
    DOUBLES_EQUAL(10.3923, av->TotalArea(), THRESH_HLOD);
}

TEST(AreaVistorTest, AreaVistor)
{
    Point_t t11 = {0.0, 0.0};
    Point_t t12 = {5.0, 0.0};
    Point_t t13 = {2.0, 1.0};
    Point_t t21 = {0.0, -2.0};
    Point_t t23 = {4, -3.0};

    Media* r = new ShapeMedia(new Rectangle(t11, 3, 2));
    Media* c = new ShapeMedia(new Circle(t11, 7));
    Media* t1 = new ShapeMedia(new Triangle(t11, t12, t13));
    Media* t2 = new ShapeMedia(new Triangle(t21, t12, t23));

    Media *cm1 = new ComboMedia(r, c);
    Media *cm2 = new ComboMedia(t1, t2);
    ComboMedia* cm = new ComboMedia(cm1, cm2);

    AreaVisitor* av = new AreaVisitor();
    cm->Accept(av);
    DOUBLES_EQUAL(168.938037, av->TotalArea(), THRESH_HLOD);
}

TEST(PerimeterVisitorTest, PerimeterVisitor)
{
    Point_t t11 = {0.0, 0.0};
    Point_t t12 = {5.0, 0.0};
    Point_t t13 = {2.0, 1.0};
    Point_t t21 = {0.0, -2.0};
    Point_t t23 = {4, -3.0};

    Media* r = new ShapeMedia(new Rectangle(t11, 3, 2));
    Media* c = new ShapeMedia(new Circle(t11, 7));
    Media* t1 = new ShapeMedia(new Triangle(t11, t12, t13));
    Media* t2 = new ShapeMedia(new Triangle(t21, t12, t23));

    Media *cm1 = new ComboMedia(r, c);
    Media *cm2 = new ComboMedia(t1, t2);
    ComboMedia* cm = new ComboMedia(cm1, cm2);

    PerimeterVisitor* pv = new PerimeterVisitor();
    cm->Accept(pv);
    DOUBLES_EQUAL(77.05119, pv->TotalPerimeter(), THRESH_HLOD);
}

#endif // UNITTEST_H_INCLUDED
