#pragma once

#include <iostream>
#include <stdexcept>

namespace mtm {

    template <typename T>
    class SortedList {
        struct Node{
            T data;
            Node* next;

            Node(T data) : data(data), next(nullptr) {}
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
        
        template <class Condition>
        SortedList filter(const Condition& condition) const;
        
        template <class Operation>
        SortedList apply(const Operation& op) const;
    };

    template <typename T>
    template <class Condition>
    SortedList<T> SortedList<T>::filter(const Condition& condition) const{
        SortedList<T> newList;

        for(typename SortedList<T>::ConstIterator it = this->begin(); it != this->end(); ++it){
            if(condition(*it)){
                newList.insert(*it);
            }
        }
        return newList;
    }

    template <typename T>
    template <class Operation>
    SortedList<T> SortedList<T>::apply(const Operation& op) const{
        SortedList<T> newList;

        for(typename SortedList<T>::ConstIterator it = this->begin(); it != this->end(); ++it){
            T opResult = op(*it);
            
            newList.insert(opResult);
        }
        return newList;
    }
    template <typename T>
    SortedList<T>& SortedList<T>::operator=(const SortedList<T>& other){
        if(this == &other){
            return *this;
        }

        SortedList<T> copyOfOther(other); // std itself deals with alloc fail as we learned

        int oldSize = this->size;
        typename SortedList<T>::Node* oldHead = this->head;

        this->head = copyOfOther.head;
        this->size = copyOfOther.size;

        copyOfOther.head = oldHead;
        copyOfOther.size = oldSize;

        return *this;
    }//the destructor is supposed to call for copyOfOther which holds the old list so we are good in the meantime
    
    template <typename T>
    SortedList<T>::SortedList() : head(nullptr), size(0){
    }

    template <typename T>
    SortedList<T>::SortedList(const SortedList<T>& other): head(nullptr), size(0){ // not sure 
        if(other.head == nullptr){
            return;
        }

        this->head = new SortedList<T>::Node(other.head->data);
        this->size++;
        const typename SortedList<T>::Node* source = other.head->next;
        typename SortedList<T>::Node* current = this->head;
        while (source){
            current->next = new SortedList<T>::Node(source->data);
            this->size++;
            current = current->next;
            source = source->next;
        }
    }

    template <typename T>
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

    template <typename T>
    SortedList<T>::~SortedList(){ 
        clearList();
    }

    template <typename T>
    int SortedList<T>::length() const { 
        return this->size;
    }

    template <typename T>
    typename SortedList<T>::ConstIterator SortedList<T>::begin() const{
        typename SortedList<T>::ConstIterator it(this->head,0);
        return it; 
    }

    template <typename T>
    typename SortedList<T>::ConstIterator SortedList<T>::end() const{
        typename SortedList<T>::ConstIterator it(nullptr, this->size);
        return it; 
    }
    
   template<typename T>
    void SortedList<T>::insert(const T &data) {
        Node *newNode = nullptr;
        try {
            newNode = new Node(data);
        } catch (const std::bad_alloc &) {
            clearList();
            throw;
        }

        if (!head || data > head->data) {
            newNode->next = head;
            head = newNode;
        } else {
            Node *current = head;
            while (current->next && current->next->data > data) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        size++;
    }
    
    template <typename T>
    void SortedList<T>::remove(const ConstIterator& cIt){
        if(this->head == nullptr || cIt.index == this->size) {
            return;
        }
        
        if(cIt.index == 0){
            typename SortedList<T>::Node* toDelete = this->head;
            this->head = this->head->next;
            delete toDelete;
            this->size--;
            return;
        }
        typename SortedList<T>::Node* target = this->head;
        typename SortedList<T>::Node* prev = nullptr;
        int currentIndex = 0;
        while (currentIndex != cIt.index){
            prev = target;
            target = target->next;
            currentIndex++;
        }
        prev->next = target->next;
        delete target;
        this->size--;
    }
    
    template <class T>
    class SortedList<T>::ConstIterator {
        const Node* node;
        int index;

        explicit ConstIterator(const Node* node, const int& index);
        
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
    SortedList<T>::ConstIterator::ConstIterator(const Node* node, const int& index)
    : node(node), index(index){}

    template <class T>
    typename SortedList<T>::ConstIterator& SortedList<T>::ConstIterator::operator=
    (const ConstIterator& cIt){
        this->index = cIt.index;
        this->node = cIt.node;
        return *this;
    }

    template <class T> 
    const T& SortedList<T>::ConstIterator::operator*(){
        return this->node->data;
    }

    template <class T>
    typename SortedList<T>::ConstIterator& SortedList<T>::ConstIterator::operator++(){
        if(this->node == nullptr){
            throw std::out_of_range("Out of range");
        }
        this->node = this->node->next;
        (this->index)++;
        
        return *this;
    }

    template <class T>
    bool SortedList<T>::ConstIterator::operator!=(const ConstIterator& cIt){
        return this->node != cIt.node;
    }
}

