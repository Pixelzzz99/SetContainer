#include "Set.h"
#include <cstring>


Set::Element::Element()
{
    this->_content = nullptr;
    this->_size = 0;
}

Set::Element::Element(void* element, size_t size)
{
    this->_content = element;
    this->_size = size;
}

Set::Element::~Element() = default;

void Set::Element::setSize(size_t size)
{
    this->_size = size;
}

size_t Set::Element::getSize()
{
    return this->_size;
}

Set::Iterator::Iterator()
{

}

Set::Iterator::~Iterator() = default;

void* Set::Iterator::getElement(size_t& size)
{
    return currentElement;
}

bool Set::Iterator::hasNext()
{
    return false;
}

void Set::Iterator::goToNext()
{
    return;
}

bool Set::Iterator::equals(Container::Iterator* right)
{
    return false;
}


//-----------------------------------------------------------------------

Set::Set(MemoryManager &mem) : AbstractSet(mem)
{
    if(_memory <= 0)
    {
        throw Container::Error("Memory is non correct");
    }
    
    this->_count_elements = 0;
    this->_memory = mem.size();
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
    if(checkMemory(size)) return 1;
    
    Element* newElement = static_cast<Element*>(alloc_mem(sizeof(Element)));
    newElement->_content = alloc_mem(size);
    newElement->setSize(size);

    std::memcpy(newElement->_content, element, size);
    if(this->_count_elements == 0)
    {
        this->_elements = new Element*[_count_elements+1];
    }
    std::cout<<(int&)newElement->_content<<std::endl;
    this->_elements[this->_count_elements] = newElement;
    std::cout<< *(int*)this->_elements[this->_count_elements]->_content << std::endl; 

    this->_memory -= size;
    this->_count_elements++;
    return 0;
}

int Set::checkMemory(size_t size)
{
    if(size <= 0 || size > this->_memory)
    {
        return 1;
    }
    return 0;
}

int Set::size()
{
    return this->_count_elements; 
}

size_t Set::max_bytes()
{
    return this->_memory;
}

Set::Iterator* Set::find(void* elem, size_t size)
{
    return new Iterator();
}

Set::Iterator* Set::newIterator()
{
    return new Iterator();
}

Set::Iterator* Set::begin()
{
    return new Iterator();
}

Set::Iterator* Set::end()
{
    return new Iterator();
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
