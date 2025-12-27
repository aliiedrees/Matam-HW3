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
         * 
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
        ConstIterator begin() const; // implemented
        ConstIterator end() const; // implemented
        void insert(const T& data); //implemented
        void remove(const ConstIterator& it); //i implemented
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
    typename SortedList<T>::ConstIterator SortedList<T>::begin() const{
        return SortedList<T>::ConstIterator::ConstIterator(this->head,0);
    }

    template <class T>
    typename SortedList<T>::ConstIterator SortedList<T>::end() const{
        return SortedList<T>::ConstIterator::ConstIterator(nullptr, size);
    }
    
    template <class T>
    void SortedList<T>::insert(const T& data){
        typename SortedList<T>::Node* current = this->head;
        typename SortedList<T>::Node* prev = this->head;

        while (current && current->data >= data){
            prev = current;
            current = (*current)->next;
        }
        typename SortedList<T>::Node newNode = new SortedList<T>::Node(data);
        if(prev == current){
            newNode.next = this->head;
            this->head = newNode;
        } else {
            newNode.next = current;
            prev.next = &newNode;
        }
    }
    
    template <class T>
    void SortedList<T>::remove(const ConstIterator& cIt){
        typename SortedList<T>::ConstIterator it = SortedList<T>::begin();
        //typename SortedList<T>::ConstIterator end = SortedList<T>::end();
        
        if(cIt.index == 0){
            this->head = this->head->next;
            delete cIt.node;
            return;
        }
        while (it.index != cIt.index - 1){
            it++;
        }
        (it.node)->next = (cIt.node)->next;
        delete cIt.node;
    }
    
    template <class T>
    class SortedList<T>::ConstIterator {
        int index;
        const Node* node;

        explicit ConstIterator(const Node& node, const int& index);
        
        friend class SortedList<T>;

    public:
        ConstIterator(const ConstIterator&) = default;
        ConstIterator& operator=(const ConstIterator& cIt);
        ~ConstIterator() = default;
        const T& operator*();
        ConstIterator& operator++();
        bool operator!=(const ConstIterator& cIt);
    };

    template <class T>
    SortedList<T>::ConstIterator::ConstIterator(const Node& node, const int& index)
    : node(node), index(index){}

    template <class T>
    typename SortedList<T>::ConstIterator& SortedList<T>::ConstIterator::operator=
    (const ConstIterator& cIt){
        this->index = cIt.index;
        this->node = cIt.node;
    }

    template <class T> 
    const T& SortedList<T>::ConstIterator::operator*(){
        return this->node->data;
    }

    template <class T>
    typename SortedList<T>::ConstIterator& SortedList<T>::ConstIterator::operator++(){
        if(!this->node){
            throw std::out_of_range;
        }
        this->node = this->node->next;
        (this->index)++;
        
        return *this;
    }

    template <class T>
    bool SortedList<T>::ConstIterator::operator!=(const ConstIterator& cIt){
        return this->index != cIt.index;
    }
}

