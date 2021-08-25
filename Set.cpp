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

//---------------------------------------------------------------------

Set::Iterator::Iterator()
{
    this->currentElement = nullptr;
}

Set::Iterator::Iterator(Element *element)
{
    this->currentElement = element;
}

Set::Iterator::~Iterator() = default;

void setCurrentElement(Element *element)
{
    this->currentElement = element;
}

void* Set::Iterator::getElement(size_t& size)
{
    if(curElement == nullptr)
    {
        throw Container::Error("Can't give element the iterator points to an empty element");
    }
    size = curElement->getSize();
    return currentElement->_content;
}

bool Set::Iterator::hasNext()
{
    return if((this->currentElement == nullptr) || (*(this->currentElement + 1) == nullptr)) ? false : true;
}

void Set::Iterator::goToNext()
{
    if(!this->hasNext())
        throw Container::Error("no next element");
    this->currentElement = *(this->currentElement + 1);
}

bool Set::Iterator::equals(Container::Iterator* right)
{
    return if((dynamic_cast<Iterator*>(right)->currentElement == this->currentElement)) ? true : false;
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

//TODO destructor
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

//TODO unique function and Sort method
int Set::insert(void* element, size_t size)
{
    if(checkMemory(size)) return 1;
    
    Element* newElement = static_cast<Element*>(alloc_mem(sizeof(Element)));
    newElement->_content = alloc_mem(size);
    newElement->setSize(size);
    std::memcpy(newElement->_content, element, size);
 
    this->_elements = new Element*[_count_elements+1];

    this->_elements[this->_count_elements] = newElement;

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

//TODO find Method
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
    if(this->empty())
        return this->Iterator();

    if(_elements[0] == nullptr)
        return this->newIterator();
    return new Iterator(_elements[0]);
}

Set::Iterator* Set::end()
{
    if(this->empty())
        return this->newIterator();

    if(_elements[0] == nullptr)
        return this->newIterator();

    return new Iterator(_elements[_count_elements-1]);
}

//TODO remove Method
void Set::remove(Container::Iterator* iter)
{
    
}
//TODO clear Method
void Set::clear()
{

}

bool Set::empty()
{
    return (this->_count_elements == 0) ? true : false;
}
