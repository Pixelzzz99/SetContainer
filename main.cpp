#include "Test.h"

int main()
{
 
    SetTests* tests = new SetTests();
    tests->simpleTest();
    tests->memTest();
    tests->insertDiffTwoElements();
    tests->insertSimilarTwoElements();
    tests->insertTenElements();
    return 0;
}
