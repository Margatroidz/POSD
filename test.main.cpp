#include <iostream>
#include "cppunitlite/TestHarness.h"
#include "UnitTest/MediaUnitTest.h"
#include "UnitTest/ShapeUnitTest.h"
#include "UnitTest/CommandUnitTest.h"

int main()
{
    TestResult testResult;
    TestRegistry::runAllTests(testResult);
}
