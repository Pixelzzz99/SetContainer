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
    

    Set::Iterator* iter = set.begin();
    size_t size;
    int element_set = *(int*)iter->getElement(size);

    if(element_set == element)
        std::cout << element_set <<std::endl;
    else return testFailed(test_name);

    return (result == 0) ? testPassed(test_name) : testFailed(test_name);
}

int SetTests::memTest()
{
    std::string test_name = "Memory Test: ";
    Mem mem(0);
    Set set(mem);
    std::cout << set.max_bytes() <<std::endl;
    if(set.max_bytes() == 0)
    {
        return testPassed(test_name);
    }
    return testFailed(test_name);
}

int SetTests::insertDiffTwoElements()
{
    std::string test_name = "Insert two different elements in set: ";
    Mem mem(100);
    Set set(mem);
    int element1 = 234;
    int element2 = 123;

    int result1 = set.insert(&element1, sizeof(element1));
    int result2 = set.insert(&element2, sizeof(element2));
 
    if(result1 != result2)
        return testFailed(test_name);
    
    /*
    Set::Iterator* iter = set.begin();
    
    while(true)
    {
        size_t size;
        std::cout<< *(int*)iter->getElement(size)<<std::endl;
        if(iter->hasNext())
        {
            iter->goToNext();
            continue;
        }
        break;
    }*/

    std::cout<<"Count elements in set EXPECTED 2: " << set.size()<<std::endl;
    return testPassed(test_name);
}

int SetTests::insertSimilarTwoElements()
{
    std::string test_name = "Insert two similar elements in set: ";
    Mem mem(100);
    Set set(mem);
    int element1 = 123;
    int element2 = 123;

    int result1 = set.insert(&element1, sizeof(element1));
    int result2 = set.insert(&element2, sizeof(element2));
 
    std::cout<<"Count elements in set EXPECTED 1: " << set.size()<<std::endl;
    if(result1 != result2)
        return testPassed(test_name);
    
    return testFailed(test_name);
}

int SetTests::insertTenElements()
{
    std::string test_name = "Insert ten elements in set: ";
    Mem mem(100);
    Set set(mem);
    std::vector<int> tenElements = {23, 34, 1, 2, 2, 4, 5, 5, 7, 23};
    for(int i = 0; i < tenElements.size(); i++)
    {
        int result = set.insert(&tenElements[i], sizeof(int));
        //std::cout<<std::endl;
    }
    
    std::cout<<"Count elements in set EXPECTED 7: " << set.size()<<std::endl;
    if(set.size() == 7)
        return testPassed(test_name);
    
    return testFailed(test_name); 
}

