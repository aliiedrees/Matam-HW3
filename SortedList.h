#pragma once

#include <iostream>
#include <stdexcept>

namespace mtm {

    template <typename T>
    class SortedList {
        class Node{
            T data;
            Node* next;

            Node(T data;) : data(data), node(nullptr) {};
        };

        Node* head;
        int size;
        
        void clearList(); //implemented
    public:
        /**
         *
         * the class should support the following public interface:
         * if needed, use =defualt / =delete
         *
         * constructors and destructor:
         * 1. SortedList() - creates an empty list.
         * 2. copy constructor
         * 3. operator= - assignment operator
         * 4. ~SortedList() - destructor
         *
         * iterator:
         * 5. class ConstIterator;
         * 6. begin method
         * 7. end method
         *
         * functions:
         * 8. insert - inserts a new element to the list
         * 9. remove - removes an element from the list
         * 10. length - returns the number of elements in the list
         * 11. filter - returns a new list with elements that satisfy a given condition
         * 12. apply - returns a new list with elements that were modified by an operation
         */
        SortedList(); // implemeneted
        ~SortedList();  // implemented
        SortedList(const SortedList& other); // working on
        SortedList& operator=(const SortedList& other);
        class ConstIterator;
        ConstIterator& begin(); // will add return value later
        ConstIterator& end(); // same for begin
        void insert(const T& data);
        void remove(const ConstIterator& it);
        int length() const; // implemented
    };

    template <class T>
    SortedList<T>::SortedList() : head(nullptr), size(0){
    }

    template <class T>
    void SortedList<T>::clearList() {
        Node* current = this->head;
        while (current){
            Node* toDelete = current;
            current = current->next;
            delete toDelete;
        }
        this->head = nullptr;
        this->size = 0;
    }

    template <class T>
    SortedList<T>::~SortedList(){ 
        clearList() 
    }

    template <class T>
    SortedList<T>::SortedList(const SortedList& other){ // didnt finish 
        const SortedList* source = other;
        SortedList* target = this->head;
        Node* nextNode = nullptr;
        while(source){
            Node node = new Node(source->head->data);
            target->head = &node;
            source->head = source->head->next;
        }
    }

    template <class T>
    int SortedList<T>::length() const { 
        return this->size;
    }

    template <class T>
    class SortedList<T>::ConstIterator {
    /**
     * the class should support the following public interface:
     * if needed, use =defualt / =delete
     *
     * constructors and destructor:
     * 1. a ctor(or ctors) your implementation needs
     * 2. copy constructor
     * 3. operator= - assignment operator
     * 4. ~ConstIterator() - destructor
     *
     * operators:
     * 5. operator* - returns the element the iterator points to
     * 6. operator++ - advances the iterator to the next element
     * 7. operator!= - returns true if the iterator points to a different element
     *
     */
    };
}

