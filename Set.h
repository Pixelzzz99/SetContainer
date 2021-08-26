#pragma once
#include "SetAbstract.h"

#include "algorithm"
#include <iostream>
#include <vector>

class Set : public AbstractSet
{
    private:
        class Element
        {
        private: 
            size_t _size;
        public:
            void* _content;
            Element();
            Element(void *element, size_t size);
            ~Element();

            void setSize(size_t size);
            size_t getSize();
        };


        size_t _memory;
        Element** _elements;
        unsigned int _count_elements;
        
        bool unique(void* element);
        Element* createNewElement(void* element, size_t size);
        Element** resizeArrayOnOneSize();
        Element** refreshElementsWithNewElement(Element* element);

    public:

        //Constructor and destructor
        Set(MemoryManager &mem);
        ~Set();

        class Iterator : public AbstractSet::Iterator
        {
        private:
            int _count_elements;
            Element* currentElement;
            Element** allElements;
            int local_index;
        public:
            Iterator();
            Iterator(Element* element, Element** elements, int count_elements);
            ~Iterator();
            
            Element* getCurrentElement();
            void setCurrentElement(Element* element);

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


        int checkMemory(size_t size);

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
