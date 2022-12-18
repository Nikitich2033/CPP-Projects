#ifndef NODE_H
#define NODE_H

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;



template<typename T>
class Node {

private:



public:

  T data;
  Node * next;
  Node * previous;

  Node(T dataIn)
    :data(dataIn){
      next = nullptr;
      previous = nullptr;
    }

};



template<typename T>
class NodeIterator {

private:

    Node<T>* current;

public:


    NodeIterator(Node<T>* currentIn)
        : current(currentIn) {
    }

    T & operator*() {
        return current->data;
    }

    // TODO: complete the code for NodeIterator here

    // prefix increment
    void operator++ (){
      current = current -> next;
    }

    bool operator==(NodeIterator rhs){
      if (this -> current == rhs.current) {
        return true;
      }
      else{
        return false;
      }
    }

    bool operator!= (NodeIterator rhs){
      if (this -> current == rhs.current) {
        return false;
      }
      else{
        return true;
      }
    }
};


template<typename T>
class NodeIteratorConst {

private:

    const Node<T>* current;

public:


    NodeIteratorConst(const Node<T>* currentIn)
        : current(currentIn) {
    }

    const T & operator*() const {
        return current->data;
    }

    // TODO: complete the code for NodeIterator here

    //prefix increment
    void operator++ (){
      current = current -> next;
    }

    const bool operator==(NodeIteratorConst rhs) const{
      if (this -> current == rhs.current) {
        return true;
      }
      else{
        return false;
      }
    }

    const bool operator!= (NodeIteratorConst rhs) const{
      if (this -> current == rhs.current) {
        return false;
      }
      else{
        return true;
      }
    }
};

// do not edit below this line

#endif
