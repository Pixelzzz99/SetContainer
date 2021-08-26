#include "Test.h"

int main()
{
 
    SetTests* tests = new SetTests();
    tests->simpleTest();
    tests->memTest();
    tests->insertDiffTwoElements();
    return 0;
}
