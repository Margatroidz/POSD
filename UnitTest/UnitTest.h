#ifndef UNITTEST_H_INCLUDED
#define UNITTEST_H_INCLUDED
#include "Shapes.h"
#include <vector>
#include <string.h>
#define THRESH_HLOD 0.00001

using namespace std;

TEST(circleTest, circle)
{
    Point_t center = {0.0, 0.0};
    Shape* circle = new Circle(center, 5);
    DOUBLES_EQUAL(78.539815, circle->area(), THRESH_HLOD);
    DOUBLES_EQUAL(31.415926, circle->perimeter(), THRESH_HLOD);
    delete circle;

    circle = new Circle(center, 0);
    DOUBLES_EQUAL(0.0, circle->area(), THRESH_HLOD);
    DOUBLES_EQUAL(0.0, circle->perimeter(), THRESH_HLOD);
    delete circle;

    try
    {
        circle = new Circle(center, -5);
    }
    catch(char const* e)
    {
        CHECK_EQUAL(ERROR, e);
        CHECK(circle == NULL);
    }
}

TEST(rectangleTest, rectangle)
{
    Point_t upperLeft = {0.0, 0.0};
    Shape* rectangle = new Rectangle(upperLeft, 4, 7);
    DOUBLES_EQUAL(28.0, rectangle->area(), THRESH_HLOD);
    DOUBLES_EQUAL(22.0, rectangle->perimeter(), THRESH_HLOD);
    delete rectangle;

    rectangle = new Rectangle(upperLeft, 0, 7);
    DOUBLES_EQUAL(0.0, rectangle->area(), THRESH_HLOD);
    DOUBLES_EQUAL(14.0, rectangle->perimeter(), THRESH_HLOD);
    delete rectangle;

    rectangle = new Rectangle(upperLeft, 4, 0);
    DOUBLES_EQUAL(0.0, rectangle->area(), THRESH_HLOD);
    DOUBLES_EQUAL(8.0, rectangle->perimeter(), THRESH_HLOD);
    delete rectangle;

    try
    {
        rectangle = new Rectangle(upperLeft, -4, 7);
    }
    catch(char const* e)
    {
        CHECK_EQUAL(ERROR, e);
        CHECK(rectangle == NULL);
    }

    try
    {
        rectangle = new Rectangle(upperLeft, 4, -7);
    }
    catch(char const* e)
    {
        CHECK_EQUAL(ERROR, e);
        CHECK(rectangle == NULL);
    }
}

TEST(triangleTest, triangle)
{
    Point_t point1 = {0.0, 0.0};
    Point_t point2 = {5.0, 0.0};
    Point_t point3 = {5.0, 5.0};
    Shape* triangle = new Triangle(point1, point2, point3);
    DOUBLES_EQUAL(12.5, triangle->area(), THRESH_HLOD);
    DOUBLES_EQUAL(17.07106781, triangle->perimeter(), THRESH_HLOD);
    delete triangle;

    try
    {
        triangle = new Triangle(point3, point3, point3);
        DOUBLES_EQUAL(0.0, triangle->area(), THRESH_HLOD);
        DOUBLES_EQUAL(0.0, triangle->perimeter(), THRESH_HLOD);
    }
    catch(char const* e)
    {
        CHECK_EQUAL(ERROR, e);
        CHECK(triangle == NULL);
    }
}

TEST(PerimeterOfShapesTest, PerimeterOfShapes)
{
    Point_t center = {0.0, 0.0};
    Shape* circle = new Circle(center, 5);
    Point_t upperLeft = {0.0, 0.0};
    Shape* rectangle = new Rectangle(upperLeft, 4, 7);
    Point_t point1 = {0.0, 0.0};
    Point_t point2 = {5.0, 0.0};
    Point_t point3 = {5.0, 5.0};
    Shape* triangle = new Triangle(point1, point2, point3);
    vector<Shape*> shapes;
    shapes.push_back(circle);
    shapes.push_back(rectangle);
    shapes.push_back(triangle);
    DOUBLES_EQUAL(70.48699381, PerimeterOfShapes(shapes), THRESH_HLOD);

    delete circle;
    delete rectangle;
    delete triangle;
}


#endif // UNITTEST_H_INCLUDED
