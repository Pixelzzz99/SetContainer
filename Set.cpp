#include "Set.h"
#include <cstring>

Set::Set(MemoryManager &mem) : AbstractSet(mem)
{
    if(_memory <= 0)
    {
        throw Container::Error("Memory is non correct");
    }
    this->_memory = _memory;
}

Set::~Set()
{
    clear();
}

void* Set::alloc_mem(size_t size)
{
    return Container::_memory.allocMem(size);
}

void Set::free_mem(void * ptr)
{
    Container::_memory.freeMem(ptr);
}

int Set::insert(void* element, size_t size)
{
    if(checkMemory(size))
    {
        return 1;
    }

    *(this->_elements + this->_count_elements) = this->alloc_mem(size);
    std::memcpy(&*(this->_elements + this->_count_elements), &element, sizeof(size));

    this->_memory -= size;
    this-_count_elements++;
    return 0;
}

int Set::checkMemory(size_t size)
{
    if((this->_memory + size) > this-> _memory)
    {
        return 1;
    }
    if(size <= 0 || size > this->_memory)
    {
        return 1;
    }
    return 0;
}

int Set::size()
{
    return this->_memory; 
}

size_t Set::max_bytes()
{
    return 0;
}

Set::Iterator* Set::find(void* elem, size_t size)
{
    return new Iterator;
}

Set::Iterator* Set::newIterator()
{
    return new Iterator;
}

Set::Iterator* Set::begin()
{
    return new Iterator;
}

Set::Iterator* Set::end()
{
    return new Iterator;
}

void Set::remove(Container::Iterator* iter)
{
    
}

void Set::clear()
{

}

bool Set::empty()
{
    return (this->_count_elements == 0) ? true : false;
}
