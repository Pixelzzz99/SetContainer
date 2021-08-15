#pragma once
#include <iostream>
#include "SetAbstract.h"

class Set : public GroupContainer 
{
private:
    size_t _memory;
    void* _elements;

public:

    //Constructor and destructor
    Set(MemoryManager &mem);
    ~Set();
    

    class Iterator : public AbstractSet::Iterator
    
    private: 

    public:
        Iterator();
        ~Iterator();

        void* getElement(size_t& size) override;
        bool hasNext() override;
        void goToNext() override;
        bool equals(Container::Iterator* right) override;
    };
    
    //Methods AbstractSet
    int insert(void *element, size_t size) override;

    //Methods for work with memory allocated
    void *alloc_mem(size_t size);
    void free_mem(void *ptr);

    
    //Standard Container Methods override
    int size() override;
    size_t max_bytes() override;
    Set::Iterator* find(void* elem, size_t size) override;
    Set::Iterator* newIterator() override;
    Set::Iterator* begin() override;
    Set::Iterator* end() override;
    void remove(Container::Iterator *iter);
    void clear() override;
    bool empty() override;

};
