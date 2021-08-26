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

int SetTests::emptyFunction()
{
    std::string test_name = "Empty function check: ";
    Mem mem(100);
    Set set(mem);
    for(int i = 0; i < 12; i++)
    {
        set.insert(&i, sizeof(i));

    }
    std::cout<<"Count elements in set EXPECTED 12 :" << set.size()<<std::endl;
    std::cout<<"Max bytes before clear function EXPECTED 52: "<<set.max_bytes()<<std::endl;
    if(set.size() != 12 || set.max_bytes() != 52)
    {
        return testFailed(test_name);
    }

    set.clear();

    std::cout<<"Count elements in set EXPECTED 0 :" << set.size()<<std::endl;
    std::cout<<"Max bytes after clear function EXPECTED 100: "<<set.max_bytes()<<std::endl;
    if(set.empty())
    {
        return testPassed(test_name);
    }
    return testFailed(test_name);
}

int SetTests::doubleClearCheck()
{
    std::string test_name = "Check double clear function: ";
    Mem mem(100);
    Set set(mem);
    for(int i = 0; i < 12; i++)
    {
        set.insert(&i, sizeof(i));

    }
    std::cout<<"Count elements in set EXPECTED 12 :" << set.size()<<std::endl;
    std::cout<<"Max bytes before clear function EXPECTED 52: "<<set.max_bytes()<<std::endl;
    if(set.size() != 12 || set.max_bytes() != 52)
    {
        return testFailed(test_name);
    }

    set.clear();
    std::cout<<"Count elements in set EXPECTED 0 :" << set.size()<<std::endl;
    std::cout<<"Max bytes after clear function EXPECTED 100: "<<set.max_bytes()<<std::endl;
    
    set.clear();
    std::cout<<"Second clear do nothing : Good"<<std::endl;
    return testPassed(test_name);
}

int SetTests::iteratorCheck()
{
    std::string test_name = "Simple iterator checker: ";
    Mem mem(100);
    Set set(mem);
    int element1 = 234;
    int element2 = 123;

    int result1 = set.insert(&element1, sizeof(element1));
    int result2 = set.insert(&element2, sizeof(element2));
 
    if(result1 != result2)
        return testFailed(test_name);
    
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
    }

    std::cout<<"Count elements in set EXPECTED 2: " << set.size()<<std::endl;
    return testPassed(test_name);
}


int SetTests::iteratorWithMoreElements()
{
    std::string test_name = "Check Iterator with more Elements: ";
    Mem mem(100);
    Set set(mem);
    std::vector<int> tenElements = {23, 34, 1, 2, 2, 4, 5, 5, 7, 23};
    for(int i = 0; i < tenElements.size(); i++)
    {
        int result = set.insert(&tenElements[i], sizeof(int));
    }
    
    std::cout<<"Count elements in set EXPECTED 7: " << set.size()<<std::endl;
 
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
    }

    return testPassed(test_name);
}

int SetTests::iteratorWithRemoveElement()
{
    std::string test_name = "Check Iterator with remove element";
    Mem mem(100);
    Set set(mem);
    for(int i = 0; i < 10; i++)
    {
        set.insert(&i, sizeof(int));
    }
    Set::Iterator* iter = set.begin();
    int delete_element=3;
    for(int i = 0; i < 10; i++)
    {
        size_t size;
        
        if(delete_element == *(int*)iter->getElement(size))
        {
            set.remove(iter);
            delete_element += 2;
        }

        if(iter->hasNext())
        {
            iter->goToNext();
        }
    }

    std::cout<<"Count elements in set EXPECTED 6: " << set.size()<<std::endl;
    if(set.size() == 6)
        return testPassed(test_name);

    return testFailed(test_name);
}
