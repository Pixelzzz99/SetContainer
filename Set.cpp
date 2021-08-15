#include "Set.h"

Set::Set(MemoryManager &mem) : GroupContainer(mem)
{
    this->_memory = mem;
}

Set::~Set()
{

}

void *Set::allocMem(size_t size)
{
    return _memory.allocMem(size);
}

void *Set::freeMem(void * ptr)
{
    _memory.freeMem(ptr)
}

int Set::insert(void* element, size_t size)
{
    void * new_element = allocMem(size);
    this->_elements = 
}

int Set::size()
{

}

size_t Set::max_bytes()
{

}

Set::Iterator* Set::find(void* elem, size_t size)
{

}

Set::Iterator* Set::newIterator()
{

}

Set::Iterator* Set::begin()
{

}

Set::Iterator* Set::end()
{

}

void remove(Container::Iterator* iter)
{

}

void clear()
{

}

bool empty()
{

}
