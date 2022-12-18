#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"
#include <initializer_list>

#include <utility>

// Do not add any #include statements here.  If you have a convincing need for adding a different `#include` please post in the forum on KEATS.

// TODO your code goes here:

template<typename T>
class LinkedList {

private:

  Node<T> *head;
  Node<T> *tail;
  int count;

public:

  LinkedList(){

    head = nullptr;
    tail = nullptr;
    count = 0;

  };


  ~LinkedList() {

    Node<T>* current = head;

    while(current != nullptr){

      Node<T>* next = current->next;
      delete current;
      current = next;
    }

 }

  void push_front(T data){

    Node<T> *newNode;

    newNode = new Node<T>(data);
    newNode -> next = head;
    newNode -> previous = nullptr;

    if (tail == nullptr) {

      tail = newNode;

    }
    else{

      head -> previous = newNode;

    }

    head = newNode;

    count++;
  }

  T front(){
    NodeIterator<int> itr(head);
    return *itr;
    //delete[] &itr;
  }


  void push_back(T data){


    Node<T> *newNode = new  Node<T>(data);
    newNode -> next = nullptr;
    newNode -> previous = tail;

    if(head == nullptr){
      head = newNode;
    }
    else{
      tail -> next = newNode;
    }

    tail = newNode;

    count++;

  }

  LinkedList(std::initializer_list<T> listIn){
    head = nullptr;
    tail = nullptr;
    count = 0;

    for(auto i =listIn.begin(); i < listIn.end(); ++i){

       push_back(*i);

    }

  }

  T back(){
    NodeIterator<int> itr(tail);
    return *itr;
    //delete[] &itr;
  }


  int size(){
    return count;
  }

  NodeIterator<T> begin(){
    return NodeIterator<T>(head);
  }

  NodeIterator<T> end(){
    return NodeIterator<T>(nullptr);
  }

  const NodeIteratorConst<T> begin() const{
    return NodeIteratorConst<T>(head);
  }

  const NodeIteratorConst<T> end() const{
    return NodeIteratorConst<T>(nullptr);
  }

  void reverse(){

    Node<T>* current = head;
    Node<T>* prev = nullptr;
    Node<T>* next = nullptr;

    while(current != nullptr){
      next = current -> next;

      current -> next = prev;

      prev = current;
      current = next;
    }

    head = prev;

  }

  NodeIterator<T> erase(NodeIterator<T> itr){

    NodeIterator<T> thisItr = begin();

    Node<T>* current = head;
    Node<T>* prev = nullptr;
    Node<T>* next = nullptr;

    if(head->data == *itr){
      current = current -> next;
      head = current;
      count--;
      return itr;
    }
    else{

      while(current -> data != *itr && current != nullptr){

        prev = current;
        current = head -> next;
        next = current -> next;
        ++thisItr;
        if (current -> data == *itr ) {
          prev -> next = next;
          next -> previous = prev;
          prev = nullptr;
        }
      }

      //for (auto it = begin(); it != end(); ++it) std::cout << *it << std::endl;
      NodeIterator<T> returnItr(next);
      count--;
      return returnItr;

    }
  }

  NodeIterator<T> insert(NodeIterator<T> itr,int data){

    NodeIterator<T> thisItr = begin();

    Node<T>* newNode = new Node<T>(data);

    Node<T>* current = head;
    Node<T>* prev = nullptr;
    Node<T>* next = nullptr;

    if(head->data == *itr){
      push_front(data);
      count++;
      return itr;
    }
    else{

      while(current -> data != *itr && current != nullptr){

        prev = current;
        current = head -> next;
        next = current -> next;
        ++thisItr;
        if (current -> data == *itr ) {
          newNode -> next = current;
          newNode -> previous = prev;
          prev -> next = newNode;
          next -> previous = newNode;

        }
      }

      //for (auto it = begin(); it != end(); ++it) std::cout << *it << std::endl;

      NodeIterator<T> returnItr(newNode);
      count--;
      return returnItr;
      }

      delete newNode;

    }

};





// do not edit below this line

#endif
