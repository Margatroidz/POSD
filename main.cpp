#include <iostream>
#include "cppunitlite/TestHarness.h"
#include "UnitTest/UnitTest.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void Run()
{
    double inputData[6] = {0, 0, 0, 0, 0, 0};
    char dump;
    vector<Shape*> shapes;

    try
    {
        //輸入格式沒有做防呆，長、寬、半徑不可為負
        /*第一題*/
        printf("Computing  the perimeter of a circle\nFormat : Input 3 number each split by a single space.(CenterX CenterY Radius)\n");
        scanf("%lf%c%lf%c%lf%c", &inputData[0], &dump, &inputData[1], &dump, &inputData[2], &dump);
        Point_t center = {inputData[0], inputData[1]};
        Shape* c = new Circle(center, inputData[2]);
        shapes.push_back(c);

        cout << c->perimeter() << endl;

        /*第二題*/
        printf("Computing  the perimeter of a rectangle\nFormat : Input 4 number each split by a single space.(upperLeftX upperLeftY width height)\n");
        scanf("%lf%c%lf%c%lf%c%lf%c", &inputData[0], &dump, &inputData[1], &dump, &inputData[2], &dump, &inputData[3], &dump);
        Point_t upperLeft = {inputData[0], inputData[1]};
        Shape* r = new Rectangle(upperLeft, inputData[2], inputData[3]);
        shapes.push_back(r);

        cout << r->perimeter() << endl;

        /*第三題*/
        printf("Creating a triangle given three points\nFormat : Input 6 number each split by a single space.(point1X point1Y point2X point2Y point3X point3Y)\n");
        scanf("%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c", &inputData[0], &dump, &inputData[1], &dump, &inputData[2], &dump, &inputData[3], &dump, &inputData[4], &dump, &inputData[5], &dump);
        Point_t point1 = {inputData[0], inputData[1]};
        Point_t point2 = {inputData[2], inputData[3]};
        Point_t point3 = {inputData[4], inputData[5]};
        Shape* t = new Triangle(point1, point2, point3);
        shapes.push_back(t);

        /*第四題*/
        printf("Computing  the perimeter of a triangle.Using triangle created by No.3\n");
        cout << t->perimeter() << endl;

        /*第五題*/
        printf("Computing  the area of a triangle.Using triangle created by No.3\n");
        cout << t->area() << endl;

        /*第六題*/
        printf("Computing the sum of perimeters of a number of shapes, including at least one of each of rectangle, circle and triangle.Using Shapes Created by No.1 ~ No.3\n");

        cout << PerimeterOfShapes(shapes) << endl;
    }
    catch(char const* e)
    {
        printf("%s\n", e);
    }
}

int main()
{
    TestResult testResult;
    TestRegistry::runAllTests(testResult);
    printf("\n");
    Run();
}
