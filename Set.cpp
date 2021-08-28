#include "Set.h"
#include <iostream>
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

Set::Iterator::Iterator(Element *element, Element** elements, int count_elements)
{
    this->currentElement = element;
    this->allElements = elements;
    this->_count_elements = count_elements;

    for(int i = 0; i < this->_count_elements; i++)
    {
        if(this->currentElement == this->allElements[i])
        {
            this->local_index = i;
        }
    }
}

Set::Iterator::~Iterator() = default;

Set::Element* Set::Iterator::getCurrentElement()
{
    return this->currentElement;
}

void Set::Iterator::setCurrentElement(Element* element)
{
    this->currentElement = element;
}

void Set::Iterator::setAllElements(Element** elements, int count, int index)
{
    this->allElements = elements;
    this->_count_elements = count;
    this->local_index = index;
}

void* Set::Iterator::getElement(size_t& size)
{
    if(currentElement == nullptr)
    {
        throw Container::Error("Can't give element the iterator points to an empty element");
    }
    size = currentElement->getSize();
    return currentElement->_content;
}

bool Set::Iterator::hasNext()
{
    if (this->currentElement == nullptr)
        return false;
    if (this->allElements[this->local_index + 1] == nullptr || this->local_index+1 == this->_count_elements)
        return false;
    return true;
}

void Set::Iterator::goToNext()
{
    if(!this->hasNext())
    {
        throw Container::Error("no next element");
    }
    this->currentElement = this->allElements[this->local_index + 1];
    this->local_index++;
}

bool Set::Iterator::equals(Container::Iterator* right)
{
    return ((dynamic_cast<Iterator*>(right)->currentElement == this->currentElement)) ? true : false;
}


//-----------------------------------------------------------------------

Set::Set(MemoryManager &mem) : AbstractSet(mem)
{
    this->_count_elements = 0;
    if(mem.size() >= 0)
        this->_memory = mem.size();
    this->_elements = new Element*[0];
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
    if(checkMemory(size)) return 2;
    if(!unique(element)) return 1;
    
    Element* newElement = this->createNewElement(element, size);
    this->_elements = this->refreshElementsWithNewElement(newElement);

    this->_memory -= size;
    this->_count_elements++;
    return 0;
}

int Set::checkMemory(size_t size)
{
    if(size <= 0 || size > this->_memory) return 1;
    return 0;
}

bool Set::unique(void* element)
{
    if(_count_elements == 0) return 1;
    for(int i = 0; i < _count_elements; i++)
    {
        if(*(int*)this->_elements[i]->_content == *(int*)element) return 0;
    }
    return 1;
}

Set::Element* Set::createNewElement(void* element, size_t size)
{
    Element* newElement = static_cast<Element*>(alloc_mem(sizeof(Element)));
    newElement->_content = alloc_mem(size);
    newElement->setSize(size);
    std::memcpy(newElement->_content, element, size);
    return newElement;
}

Set::Element** Set::resizeArrayOnOneSize()
{
    Element** tempElements = new Element*[_count_elements+1];
    std::memcpy(tempElements, this->_elements, _count_elements * sizeof(Element*));
    return tempElements;
}

Set::Element** Set::refreshElementsWithNewElement(Element* element)
{
    Element** elements = this->resizeArrayOnOneSize();
    elements[_count_elements] = element;
    std::sort(elements, elements + _count_elements + 1, [](Element* a, Element* b) 
            {
                return *(int*)a->_content < *(int*)b->_content; 
            });
    delete[] this->_elements;
    return elements;
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
    if(this->empty())
        return new Iterator();
    
    Iterator* iter = this->begin();
    size_t local_size;
    int currentElement = 0;
    bool success = false;
    int count_elements = this->_count_elements;
    while(true)
    {
        currentElement = *(int*)iter->getElement(local_size);
        if(currentElement == *(int*)elem && local_size == size)
        {
            success = true;
            break;
        }

        if(count_elements == 0)
            break; 
        
        count_elements--;
        if(iter->hasNext())
            iter->goToNext();
    }
    return (success) ? iter : this->newIterator();
}

Set::Iterator* Set::newIterator()
{
    return new Iterator();
}

Set::Iterator* Set::begin()
{
    if(this->empty())
        return this->newIterator();

    if(_elements[0] == nullptr)
        return this->newIterator();
    return new Iterator(_elements[0], _elements, this->_count_elements);
}

Set::Iterator* Set::end()
{
    if(this->empty())
        return this->newIterator();

    if(_elements[0] == nullptr)
        return this->newIterator();

    return new Iterator(_elements[_count_elements-1], _elements, this->_count_elements);
}

void Set::remove(Container::Iterator* iter)
{
    if(this->empty())
        return;
    Set::Iterator* iterator = (Set::Iterator*)iter;
    Element* element = iterator->getCurrentElement();
    Element** newElements = new Element*[this->_count_elements - 1];
    

    int temp_index = 0;
    int new_index_iterator = 0;
    bool flag = false;
    for(int i = 0; i < this->_count_elements - 1; i++)
    {
        if(*(int*)this->_elements[temp_index]->_content == *(int*)element->_content)
        {
            flag = true;
            new_index_iterator = temp_index;
            temp_index++;
            iterator->goToNext();
        }
        newElements[i] = this->_elements[temp_index];
        
        temp_index++;
    }
    new_index_iterator = (!flag) ? temp_index : new_index_iterator;  

    delete[] this->_elements;
    this->_elements = newElements;

    this->_count_elements--;
    this->_memory += element->getSize(); 
    iterator->setAllElements(this->_elements, this->_count_elements,  new_index_iterator);
    this->free_mem(element->_content);
    this->free_mem(element);
}

void Set::clear()
{
    int size = this->_count_elements;
    
    if(size == 0) return ;

    for(int i = 0; i < size; i++ )
    {
        this->_memory += this->_elements[i]->getSize();
        free_mem(this->_elements[i]->_content);
        free_mem(this->_elements[i]);
        this->_count_elements--;
    }
}

bool Set::empty()
{
    return (this->_count_elements == 0) ? true : false;
}
