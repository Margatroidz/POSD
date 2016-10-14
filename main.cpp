#include <iostream>
#include "cppunitlite/TestHarness.h"
#include "UnitTest/MediaUnitTest.h"
#include "UnitTest/ShapeUnitTest.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main()
{
    TestResult testResult;
    TestRegistry::runAllTests(testResult);
    printf("\n");
}
