#include <iostream>

#include "types.h"


#ifndef SCOUNDREL_LINKED_LIST
#define SCOUNDREL_LINKED_LIST

namespace Scoundrel {

  template <typename T>
  class LinkedList {
  //TODO: Make this a legitimate intrusive list, but this works for now
  public:
    struct Node {
      Node* prev;
      Node* next;
      T data;
    };

    struct iter {
      Node* head, *tail;
      Node* current;
      Node* next() {
        if (current)
          current = current->next;
        else
          current = head;

        return current;
      }

      bool end() {
        return current == tail;
      }

      T data() {
        if (current) {
          return current->data;
        }
        return static_cast<T>(NULL);
      }
    };

    LinkedList<T>() {
      _tail = _head = NULL;
      _length = 0;
    }

    ~LinkedList<T>() {
      clear();
    }

    void clear() {
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

    void insert(T data, U32 index) {
      Node* ptr;
      if (index >= _length) {
        append(data);
        return;
      }

      ptr = _head;
      for (U32 i; i < index; ++i)
        ptr = ptr->next;

      if (!ptr) { // first element in the list
        _head = new Node();
        _head->data = data;
        _tail = _head;
      } else {
        Node* new_node = new Node();
        new_node->data = data;

        if (ptr->prev) {
          ptr->prev->next = new_node;
          new_node->prev = ptr->prev;
        }

        new_node->next = ptr;
        ptr->prev = new_node;

        if (ptr == _head)
          _head = new_node;
      }
    }

    T remove(U32 index) {
      Node* ptr;
      if (index > _length-1)
        return static_cast<T>(NULL);

      ptr = _head;
      for (U32 i; i < index; ++i)
        ptr = ptr->next;

      Node* prev, *next;
      T data;
      data = ptr->data;

      delete_node(ptr);

      return data;
    }

    void delete_node(Node* node) {
      if (node) {
        if (node->prev)
          node->prev->next = node->next;
        else
          _head = node->next;

        if (node->next)
          node->next->prev = node->prev;
        else
          _tail = node->prev;

        delete node;
      }
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

    T first() {
      if (_head)
        return _head->data;
      else
        return static_cast<T>(NULL);
    }

    T last() {
      if (_tail)
        return _tail->data;
      else
        return static_cast<T>(NULL);
    }

    iter get_iterator() {
      iter i;
      i.head = _head;
      i.tail = _tail;
      i.current = NULL;
      return i;
    }


  private:
    Node* _head;
    Node* _tail;
    U32 _length;
  };
}


#endif
