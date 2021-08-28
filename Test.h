#pragma once 
#include <iostream>
#include <string>
#include "Set.h"
#include "Mem.h"

class SetTests
{
private: 
    int testFailed(std::string test_name);
    int testPassed(std::string test_name);
public:
    SetTests();
    ~SetTests() = default;
    int simpleTest();
    int memTest();
    int insertDiffTwoElements();
    int insertSimilarTwoElements();
    int insertTenElements();
    int emptyFunction();
    int doubleClearCheck();
    int iteratorCheck();
    int iteratorWithMoreElements();
    int iteratorWithRemoveElement();
    int removeFirstElement();
    int removeLastElement();
    int removeAllElementsWithoutClear();
    int findFunction();
    int findFunctionNothing();
    int findFunctionIfSetEmpty();
    int iteratorEquals();
};
