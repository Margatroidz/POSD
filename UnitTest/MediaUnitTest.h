#ifndef UNITTEST_H_INCLUDED
#define UNITTEST_H_INCLUDED
#include "Media.h"
#include "Shapes.h"
#include "Document.h"
#include <vector>
#include <string.h>
#define THRESH_HLOD 0.00001
#include <iostream>

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
    delete r;
    delete t1;
    delete t2;
    delete cm;
    delete av;
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

    delete r;
    delete c;
    delete t1;
    delete t2;
    delete cm;
    delete cm1;
    delete cm2;
    delete av;
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

    delete r;
    delete c;
    delete t1;
    delete t2;
    delete cm;
    delete cm1;
    delete cm2;
    delete pv;
}

TEST(ShapeMediaBuilderTest, ShapeMediaBuilder)
{
    ShapeMediaBuilder* sMB = new ShapeMediaBuilder();
    try
    {
        sMB->BuildComboMedia();
        FAIL("ShapeMediaBuilder -> BuildComboMedia ERROR");
    }
    catch(const char* e)
    {
        CHECK(strcmp("can't build combo !", e) == 0);
    }
    Circle c(Point_t{0, 0}, 5);
    sMB->BuildShapeMedia(&c);
    Media* m = sMB->GetMedia();
    ShapeMedia* sm = (ShapeMedia*)m;
    DOUBLES_EQUAL(78.539815, sm->Area(), THRESH_HLOD);
    DOUBLES_EQUAL(31.415926, sm->Perimeter(), THRESH_HLOD);

    delete sMB;
}

TEST(ComboMediaBuilderTest, ComboMediaBuilder)
{
    ComboMediaBuilder* cMB = new ComboMediaBuilder();
    try
    {
        Shape* s = 0;
        cMB->BuildShapeMedia(s);
        FAIL("ShapeMediaBuilder -> BuildComboMedia ERROR");
    }
    catch(const char* e)
    {
        CHECK(strcmp("need a combo !", e) == 0);
    }
    ComboMediaBuilder* cMB2 = new ComboMediaBuilder();
    ComboMediaBuilder* cMB3 = new ComboMediaBuilder();
    Rectangle r1(Point_t{10, 0}, 15, 5);
    Circle c1(Point_t{12, 5}, 2);
    Rectangle r2(Point_t{0, 0}, 25, 20);
    Triangle t1(Point_t{0, 20}, Point_t{16, 32}, Point_t{25, 20});

    cMB->BuildComboMedia();
    cMB->BuildShapeMedia(&r1);
    cMB->BuildShapeMedia(&c1);
    cMB2->BuildComboMedia();
    cMB2->BuildShapeMedia(cMB->GetMedia());
    cMB2->BuildShapeMedia(&r2);
    cMB3->BuildComboMedia();
    cMB3->BuildShapeMedia(cMB2->GetMedia());
    cMB3->BuildShapeMedia(&t1);

    DescriptionVisitor* dv = new DescriptionVisitor();
    try
    {
        cMB3->GetMedia()->Accept(dv);
    }
    catch( const char* e )
    {
        std::cout << e << endl;
    }
    CHECK(strcmp(dv->Description().c_str(), "combo(combo(combo(r(10 0 15 5) c(12 5 2) )r(0 0 25 20) )t(0 20 16 32 25 20) )") == 0);

    delete cMB;
    delete cMB2;
    delete cMB3;
    delete dv;
}

TEST(TextMediaTest, TextMedia)
{
    TextMedia* tm = new TextMedia(new Rectangle(Point_t{0, 0}, 10, 3), "Hello !");

    CHECK(strcmp(tm->Text().c_str(), "Hello !") == 0);
}

TEST(RemoveMediaTest, RemoveMedia)
{
    ComboMediaBuilder* cMB = new ComboMediaBuilder();
    try
    {
        Shape* s = 0;
        cMB->BuildShapeMedia(s);
        FAIL("ShapeMediaBuilder -> BuildComboMedia ERROR");
    }
    catch(const char* e)
    {
        CHECK(strcmp("need a combo !", e) == 0);
    }
    ComboMediaBuilder* cMB2 = new ComboMediaBuilder();
    ComboMediaBuilder* cMB3 = new ComboMediaBuilder();
    Rectangle r1(Point_t{10, 0}, 15, 5);
    Circle c1(Point_t{12, 5}, 2);
    Triangle t1(Point_t{0, 20}, Point_t{16, 32}, Point_t{25, 20});
    Media* r;

    cMB->BuildComboMedia();
    cMB->BuildShapeMedia(&r1);
    cMB->BuildShapeMedia(&c1);
    cMB2->BuildComboMedia();
    cMB2->BuildShapeMedia(cMB->GetMedia());
    //這邊new Media而不是shape來拿media的指標
    cMB2->BuildShapeMedia(r = new ShapeMedia(new Rectangle(Point_t{0, 0}, 25, 20)));
    cMB3->BuildComboMedia();
    cMB3->BuildShapeMedia(cMB2->GetMedia());
    cMB3->BuildShapeMedia(&t1);

    DescriptionVisitor* dv = new DescriptionVisitor();
    cMB3->GetMedia()->Accept(dv);
    CHECK(strcmp(dv->Description().c_str(), "combo(combo(combo(r(10 0 15 5) c(12 5 2) )r(0 0 25 20) )t(0 20 16 32 25 20) )") == 0);
    delete dv;

    cMB3->RemoveMedia(r);
    dv = new DescriptionVisitor();
    cMB3->GetMedia()->Accept(dv);
    CHECK(strcmp(dv->Description().c_str(), "combo(combo(combo(r(10 0 15 5) c(12 5 2) ))t(0 20 16 32 25 20) )") == 0);

    delete cMB;
    delete cMB2;
    delete cMB3;
    delete dv;
}

TEST(DocumentTest, Document)
{
    Document* doc = new MyDocument();
    const char* result = doc->openDocument("test.txt").c_str();
    CHECK(strcmp(result, "combo(r(0 0 3 2) c(0 0 5) combo(r(0 0 5 4) c(0 0 10) )combo(r(0 1 8 7) c(0 1 10) ))") == 0);

    try
    {
        doc->openDocument("test").c_str();
        FAIL("Error");
    }
    catch(string ex)
    {
        CHECK(strcmp(ex.c_str(), "file is not existed.") == 0);
    }
    delete doc;
}

TEST(MediaDirectorTest, MediaDirector)
{
    Document* doc = new MyDocument();
    MediaDirector dir;
    dir.concrete(doc->openDocument("test.txt"));
    DescriptionVisitor dv;
    dir.GetMedia()->Accept(&dv);
    CHECK(strcmp(dv.Description().c_str(), "combo(r(0 0 3 2) c(0 0 5) combo(r(0 0 5 4) c(0 0 10) )combo(r(0 1 8 7) c(0 1 10) ))") == 0);
    delete doc;
}

#endif // UNITTEST_H_INCLUDED
