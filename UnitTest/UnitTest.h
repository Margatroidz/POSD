#ifndef UNITTEST_H_INCLUDED
#define UNITTEST_H_INCLUDED
#include "Shapes.h"
#include <vector>
#include <string.h>
#define THRESH_HLOD 0.00001

using namespace std;

TEST(circleTest, circlePerimeter)
{
    Point_t center = {0.0, 0.0};
    Shape* circle = new Circle(center, 5);
    DOUBLES_EQUAL(31.415926, circle->Perimeter(), THRESH_HLOD);
    delete circle;
}

TEST(circleTest, circleArea)
{
    Point_t center = {0.0, 0.0};
    Shape* circle = new Circle(center, 5);
    DOUBLES_EQUAL(78.539815, circle->Area(), THRESH_HLOD);
    delete circle;
}

TEST(circleTest, circleAConstructer)
{
    Point_t center = {0.0, 0.0};
    Shape* circle = NULL;
    try
    {
        circle = new Circle(center, -5);
    }
    catch(char const* e)
    {
        CHECK(strcmp(ERROR, e) == 0);
        CHECK(circle == NULL);
    }
}

TEST(rectangleTest, rectanglePerimeter)
{
    Point_t upperLeft = {0.0, 0.0};
    Shape* rectangle = new Rectangle(upperLeft, 4, 7);
    DOUBLES_EQUAL(22.0, rectangle->Perimeter(), THRESH_HLOD);
    delete rectangle;
}

TEST(rectangleTest, rectangleArea)
{
    Point_t upperLeft = {0.0, 0.0};
    Shape* rectangle = new Rectangle(upperLeft, 0, 7);
    DOUBLES_EQUAL(0.0, rectangle->Area(), THRESH_HLOD);
    delete rectangle;
}

TEST(rectangleTest, rectangleConstructer)
{
    Point_t upperLeft = {0.0, 0.0};
    Shape* rectangle = NULL;
    try
    {
        rectangle = new Rectangle(upperLeft, -4, 7);
    }
    catch(char const* e)
    {
        CHECK(strcmp(ERROR, e) == 0);
        CHECK(rectangle == NULL);
    }
}

TEST(triangleTest, trianglePerimeter)
{
    Point_t point1 = {0.0, 0.0};
    Point_t point2 = {5.0, 0.0};
    Point_t point3 = {5.0, 5.0};
    Shape* triangle = new Triangle(point1, point2, point3);
    DOUBLES_EQUAL(17.07106781, triangle->Perimeter(), THRESH_HLOD);
    delete triangle;
}

TEST(triangleTest, triangleArea)
{
    Point_t point1 = {0.0, 0.0};
    Point_t point2 = {5.0, 0.0};
    Point_t point3 = {5.0, 5.0};
    Shape* triangle = new Triangle(point1, point2, point3);
    DOUBLES_EQUAL(12.5, triangle->Area(), THRESH_HLOD);
    delete triangle;
}

TEST(triangleTest, triangleConstructer)
{
    Point_t point3 = {5.0, 5.0};
    Shape* triangle = NULL;
    try
    {
        triangle = new Triangle(point3, point3, point3);
        DOUBLES_EQUAL(0.0, triangle->Area(), THRESH_HLOD);
        DOUBLES_EQUAL(0.0, triangle->Perimeter(), THRESH_HLOD);
    }
    catch(char const* e)
    {
        CHECK(strcmp(ERROR, e) == 0);
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

TEST(MaxAreaTest, MaxArea)
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
    CHECK(shapes[0] == MaxArea(shapes));

    delete circle;
    delete rectangle;
    delete triangle;
}

TEST(SortByDecreasingPerimeterTest, SortByDecreasingPerimeter)
{
    Point_t center = {0.0, 0.0};
    Shape* circle = new Circle(center, 5);
    Shape* rectangle = new Rectangle(center, 40, 7);
    Point_t point1 = {0.0, 0.0};
    Point_t point2 = {5.0, 0.0};
    Point_t point3 = {5.0, 5.0};
    Shape* triangle = new Triangle(point1, point2, point3);
    Shape* bigCircle = new Circle(center, 50);
    vector<Shape*> shapes;
    shapes.push_back(circle);
    shapes.push_back(rectangle);
    shapes.push_back(triangle);
    shapes.push_back(bigCircle);
    vector<Shape*> result = SortByDecreasingPerimeter(shapes);
    DOUBLES_EQUAL(314.159260, result[0]->Perimeter(), THRESH_HLOD);
    DOUBLES_EQUAL(94, result[1]->Perimeter(), THRESH_HLOD);
    DOUBLES_EQUAL(31.415926, result[2]->Perimeter(), THRESH_HLOD);
    DOUBLES_EQUAL(17.071068, result[3]->Perimeter(), THRESH_HLOD);

    delete circle;
    delete rectangle;
    delete triangle;
    delete bigCircle;
}

TEST(ComboShapeTest, ComboShapeConstructer)
{
    Point_t center = {0.0, 0.0};
    Shape* circle = new Circle(center, 5);
    Shape* rectangle = new Rectangle(center, 40, 7);
    ComboShape* comboShape = new ComboShape(circle, rectangle);

    DOUBLES_EQUAL(358.539815, comboShape->Area(), THRESH_HLOD);
    DOUBLES_EQUAL(125.415926, comboShape->Perimeter(), THRESH_HLOD);

    delete rectangle;
    delete circle;
    delete comboShape;
}

TEST(ComboShapeTest, ComboShapeAdd)
{
    Point_t center = {0.0, 0.0};
    Shape* circle = new Circle(center, 5);
    Shape* rectangle = new Rectangle(center, 40, 7);
    Point_t point1 = {0.0, 0.0};
    Point_t point2 = {5.0, 0.0};
    Point_t point3 = {5.0, 5.0};
    Shape* triangle = new Triangle(point1, point2, point3);
    ComboShape* comboShape = new ComboShape(circle, rectangle);
    comboShape->Add(triangle);

    DOUBLES_EQUAL(371.039815, comboShape->Area(), THRESH_HLOD);
    DOUBLES_EQUAL(142.486994, comboShape->Perimeter(), THRESH_HLOD);

    delete circle;
    delete rectangle;
    delete triangle;
    delete comboShape;
}

TEST(ComboShapeTest, ComboShapeArea)
{
    Point_t center = {0.0, 0.0};
    Shape* circle = new Circle(center, 5);
    Shape* rectangle = new Rectangle(center, 7, 2);
    ComboShape* comboShape = new ComboShape(circle, rectangle);

    DOUBLES_EQUAL(92.539815, comboShape->Area(), THRESH_HLOD);

    Point_t point1 = {0.0, 0.0};
    Point_t point2 = {4.0, 0.0};
    Point_t point3 = {4.0, 4.0};
    Shape* triangle = new Triangle(point1, point2, point3);
    comboShape->Add(triangle);

    DOUBLES_EQUAL(100.539815, comboShape->Area(), THRESH_HLOD);

    delete rectangle;
    delete circle;
    delete comboShape;
}

TEST(ComboShapeTest, ComboShapePerimeter)
{
    Point_t center = {0.0, 0.0};
    Shape* circle = new Circle(center, 12);
    Shape* rectangle = new Rectangle(center, 40, 7);
    ComboShape* comboShape = new ComboShape(circle, rectangle);

    DOUBLES_EQUAL(169.398222, comboShape->Perimeter(), THRESH_HLOD);

    Point_t point1 = {0.0, 0.0};
    Point_t point2 = {4.0, 0.0};
    Point_t point3 = {4.0, 4.0};
    Shape* triangle = new Triangle(point1, point2, point3);
    comboShape->Add(triangle);

    DOUBLES_EQUAL(183.055077, comboShape->Perimeter(), THRESH_HLOD);

    delete rectangle;
    delete circle;
    delete comboShape;
}

#endif // UNITTEST_H_INCLUDED
