// header file for the templated DLList

#ifndef TEMPLATEDDLLIST_H
#define TEMPLATEDDLLIST_H

#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class DLList; // class declaration

// doubly linked list node
template <typename T>
struct DLListNode {
  T obj;
  DLListNode<T> *prev, *next;
  // constructor
  DLListNode(T e=T(), DLListNode *p=nullptr, DLListNode *n=nullptr): obj(e), prev(p), next(n) {}
};

// doubly linked list class
template <typename T>
class DLList {
private:
  DLListNode<T> header, trailer;
public:
  // default constructor
  DLList() {
    header.next = &trailer;
    trailer.prev = &header;
    header.prev = nullptr;
    //header.obj = 0;
    trailer.next = nullptr;
    //trailer.obj = 0;
  }
  // copy constructor
  DLList(const DLList<T>& dll) {
    if (dll.is_empty()) {
        header.next = &trailer;
        trailer.prev = &header;
    }
    DLListNode<T>* copy = dll.header.next;
    header.next = &trailer;
    trailer.prev = &header;
    while (copy != &dll.trailer) {
        insert_last(copy->obj);
        copy = copy->next;
    }
  }
 // move constructor
  DLList(DLList<T>&& dll) {
    if (dll.is_empty()) {
        header.next = &trailer;
        trailer.prev = &header;
    }
    else {
        header.next = dll.header.next;
        trailer.prev = dll.trailer.prev;
        dll.header.next->prev = &header;
        dll.trailer.prev->next = &trailer;
        //deallocate
        dll.header.next = &dll.trailer;
        dll.trailer.prev = &dll.header;
    }
  }
 // destructor
  ~DLList() {
    if (is_empty()) {
        return;
    }
    else {
        while (!is_empty()) {
            remove_first();
        }
    }
  }
   // copy assignment operator
  DLList<T>& operator=(const DLList<T>& dll) {
    while (!is_empty()) {
        remove_first();
    }
    DLListNode<T>* copy = dll.header.next;
    header.next = &trailer;
    trailer.prev = &header;
    while (copy != &dll.trailer) {
        this->insert_last(copy->obj);
        copy = copy->next;
    }
    return *this;
  }
  // move assignment operator
  DLList<T>& operator=(DLList<T>&& dll) {
    if (this != &dll) {
        while (!is_empty()) {
            remove_first();
        }
        if (dll.is_empty()) {
            header.next = &trailer;
            trailer.prev = &header;
        }
        else {
            header.next = dll.header.next;
            header.next->prev = &header;
            trailer.prev = dll.trailer.prev;
            trailer.prev->next = &trailer;

            dll.header.next = &dll.trailer;
            dll.trailer.prev = &dll.header;
        }
    }
    return *this;
  }
  
  // return the pointer to the first node
  DLListNode<T> *first_node() const { return header.next; } 
  
  // return the pointer to the trailer
  const DLListNode<T> *after_last_node() const { return &trailer; }
  
  // return if the list is empty
  bool is_empty() const { return header.next == &trailer; }
  // return the first object
  T first() const {
    return header.next->obj;
  }
  // return the last object
  T last() const {
    return trailer.prev->obj;
  }
  // insert to the first node
  void insert_first(T obj) {
    DLListNode<T>* newNode = new DLListNode<T>();
    newNode->obj = obj;
    newNode->prev = &header;
    newNode->next = header.next;
    header.next->prev = newNode;
    header.next = newNode;
  } 
  // remove the first node
  T remove_first() {
    exception empty;
    if (is_empty()) {
        throw empty;
    }
    DLListNode<T>* newNode = header.next; //assigns newNode to the first node
    newNode->next->prev = &header; //points the next node's previous to the header
    header.next = newNode->next; //points header's next to newNode's next
    T nObj = newNode->obj;
    delete newNode;
    return nObj;
  }
  // insert to the last node
  void insert_last(T obj) {
    DLListNode<T>* newNode = new DLListNode<T>();
    newNode->obj = obj;
    newNode->next = &trailer;
    newNode->prev = trailer.prev;
    trailer.prev->next = newNode;
    trailer.prev = newNode;
  } 
  // remove the last node
  T remove_last() {
    exception empty;
    if (is_empty()) {
        throw empty;
    }
    DLListNode<T>* newNode = trailer.prev;
    newNode->prev->next = &trailer;
    trailer.prev = newNode->prev;
    T nObj = newNode->obj;
    return nObj;
  } 
  
  void insert_after(DLListNode<T> &p, T obj) {
    exception empty;
    try {
        if (is_empty()) {
            throw empty;
        }
    } catch (exception& e) {
        cout << e.what() << endl;
    }
    DLListNode<T>* newNode = new DLListNode<T>(); //create new node
    newNode->obj = obj; //put in data
    newNode->next = p.next; //makes next of new as next of p
    newNode->prev = &p;
    p.next->prev = newNode;
    p.next = newNode;   //move next of p as new
  }
  
  void insert_before(DLListNode<T> &p, T obj) {
    exception empty;
    try {
        if (is_empty()) {
            throw empty;
        }
    } catch (exception& e) {
        cout << e.what() << endl;
    }
    DLListNode<T>* newNode = new DLListNode<T>();
    newNode->obj = obj;
    newNode->prev = p.prev; //connects node's prev to node before p
    newNode->next = &p; //connects node's next to p
    p.prev->next = newNode; 
    p.prev = newNode;
  }
  
  T remove_after(DLListNode<T> &p) {
    exception empty;
    exception bounds;
    if (is_empty()) {
        throw empty;
    }
    if (p.next == &trailer) {
        throw bounds;
    }
    DLListNode<T>* newNode = p.next;
    T removeO = newNode->obj;
    newNode->next->prev = &p;
    p.next = newNode->next;
    delete newNode;
    return removeO;
  }
  
  T remove_before(DLListNode<T> &p) {
    exception empty;
    exception bounds;
    if (is_empty()) {
        throw empty;
    }
    if (p.next == &trailer) {
        throw bounds;
    }
    DLListNode<T>* newNode = p.prev;
    T removeO = newNode->obj;
    newNode->prev->next = &p;
    p.prev = newNode->prev;
    delete newNode;
    return removeO;
  }
};

// output operator
template <typename T>
ostream& operator<<(ostream& out, const DLList<T>& dll) {
  DLListNode<T>* it = dll.first_node();
  while (it != dll.after_last_node()) {
    out << it->obj << ", ";
    it = it->next;
  }
  return out;
}


#endif
