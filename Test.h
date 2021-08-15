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
};
