#include "Test.h"

int main()
{
 
    SetTests* tests = new SetTests();
    tests->simpleTest();
    tests->memTest();
    tests->insertDiffTwoElements();
    tests->insertSimilarTwoElements();
    tests->insertTenElements();
    tests->emptyFunction();
    tests->doubleClearCheck();
    tests->iteratorCheck();
    tests->iteratorWithMoreElements();
    tests->iteratorWithRemoveElement();
    tests->removeFirstElement();
    tests->removeLastElement();
    tests->removeAllElementsWithoutClear();
    tests->findFunction();
    tests->findFunctionNothing();
    tests->findFunctionIfSetEmpty();
    return 0;
}
