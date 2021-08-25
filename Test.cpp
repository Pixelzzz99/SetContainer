#include "Test.h"

SetTests::SetTests()
{

}

int SetTests::testFailed(std::string test_name)
{
    std::cout << test_name + "Failed" <<std::endl;
    return 0;
}

int SetTests::testPassed(std::string test_name)
{
    std::cout << test_name + "Passed" <<std::endl;
    return 0;
}

int SetTests::simpleTest()
{
    std::string test_name = "Simple Test for put element in Set: ";
    Mem mem(100);
    Set set(mem);
    int element = 234;
    int result = set.insert(&element, sizeof(int));
    return (result == 0) ? testPassed(test_name) : testFailed(test_name);
}
