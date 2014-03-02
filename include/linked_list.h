#include <iostream>

#include "types.h"


#ifndef SCOUNDREL_LINKED_LIST
#define SCOUNDREL_LINKED_LIST

namespace Scoundrel {

  template <typename T>
  class LinkedList {
  //TODO: Make this a legitimate intrusive list, but this is works for now
  public:
    struct Node {
      Node* prev;
      Node* next;
      T data;
    };
    LinkedList<T>() {
      _tail = _head;
    }

    ~LinkedList<T>() {
      Node* ptr = _head;
      Node* next;
      while (ptr) {
        next = ptr->next;
        delete ptr;
        ptr = next;
      }
      _head = _tail = NULL;
    }

    void append(T data) {
      Node* next = new Node();
      next->data = data;

      if (!_head) {
        _head = next;
        _tail = _head;
      } else {
        next->prev = _tail;
        _tail->next = next;
        _tail = next;
      }
      _length += 1;
    }

    T pop() {
      if (!_tail) {
        return static_cast<T>(NULL);
      }
      T data = _tail->data; 
      Node* prev = _tail->prev;
      delete _tail;
      _tail = prev;

      if (!_tail) { //Popped the last element off
        _tail = NULL;
        _head = NULL;
      } else {
        _tail->next = NULL;
      }
      return data;
    }

    T remove(U32 index) {
      Node* ptr;
      if (index < 0)
        return static_cast<T>(NULL);

      if (index > _length-1)
        return static_cast<T>(NULL);

      ptr = _head;
      for (U32 i; i <= index; ++i)
        ptr = ptr->next;

      Node* prev, *next;
      T data;
      prev = ptr->prev;
      next = ptr->next;
      data = ptr->data;

      if (prev)
        prev->next = next;
      if (next)
        next->prev = prev;

      return data;
    }

    U32 length() {
      return _length;
    }

    void print() {
      Node* ptr = _head;
      while (ptr) {
        std::cout << ptr->data << std::endl;
        ptr = ptr->next;
      }
    }

  private:
    Node * _head;
    Node * _tail;
    U32 _length;


  };
}


#endif
