#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::ostream;

#include <memory>
using std::unique_ptr;

#include <utility>
using std::pair;

// TODO your code for the TreeNode class goes here:
template<typename T>
class TreeNode {

private:



public:

  T data;
  unique_ptr<TreeNode> leftChild;
  unique_ptr<TreeNode> rightChild;
  TreeNode * parent;

  TreeNode(T dataIn)
    :data(dataIn){

      parent = nullptr;

    }

    void setLeftChild(TreeNode* child){
      leftChild = unique_ptr<TreeNode>(child);
      leftChild -> parent = this;
    }

    void setRightChild(TreeNode* child){
      rightChild = unique_ptr<TreeNode>(child);
      rightChild -> parent = this;
    }

    void write(ostream& os) const
    {
      if(leftChild != nullptr && rightChild != nullptr){
        leftChild -> write(os);
        os << " " << data << " ";
        rightChild -> write(os);
      }
      else if(leftChild != nullptr){
        leftChild -> write(os);
        os << " " << data << " ";
      }
      else if(rightChild != nullptr){
        os << " " << data << " ";
        rightChild -> write(os);
      }
      else{
        os << " "  << data << " " ;
      }
    }

    int checkDepth(TreeNode<T> * root) {

      if (root == nullptr){

         return 0;

        }
        else{

          int leftChildDepth = checkDepth(root->leftChild.get()) + 1;
          int rightChildDepth = checkDepth(root->rightChild.get()) + 1;

          if(leftChildDepth > rightChildDepth){

            return leftChildDepth;

          }
          else{

            return rightChildDepth;

        }
      }
    }

    int maxDepth(TreeNode<T> * root) {
      return checkDepth(root);
    }

};

template<typename T>
class TreeNodeIterator {

private:

 TreeNode<T>* currentNode;

 TreeNode<T>* tempNodeRoot;

public:

 TreeNodeIterator(TreeNode<T>* currentNode) : currentNode(currentNode) {}

   T& operator*() {

       return currentNode->data;

   }

   bool operator==(const TreeNodeIterator& inputNode) {

     return currentNode == inputNode.currentNode;

   }

   bool operator!=(const TreeNodeIterator& inputNode) {

     return !(currentNode == inputNode.currentNode);

   }

   //because the node with the higher value is not always below the current
   //have to account for cases where we have to go up the tree to find the node with the next value

    TreeNode<T>* PreviousOrNext(TreeNode<T>* root, TreeNode<T>* previous, TreeNode<T>* next, int data) {

      if (root == nullptr){
         return root;
      }

      if(root -> data == data){

        if(root -> leftChild != nullptr){
          TreeNode<T> * tempNode = root->leftChild.get();

          while (tempNode->rightChild.get()) {
            tempNode = tempNode->rightChild.get();
          }

          previous = tempNode;
        }

        if(root -> rightChild != nullptr){

          TreeNode<T>* tempNode = root->rightChild.get();

          while (tempNode->leftChild.get()) {

            tempNode = tempNode->leftChild.get();

          }

          previous = tempNode;
        }
      }

      return next;


      if(root -> data > data){

        next = root;
        PreviousOrNext(root->leftChild.get(), previous, next, data);

      }
      else{

        previous = root;
        PreviousOrNext(root->rightChild.get(), previous, next, data);

      }

    }

    void operator++() {

      TreeNode<T>* previous = nullptr;

      TreeNode<T>* next = nullptr;

      currentNode = PreviousOrNext(currentNode, previous, next, currentNode->data);

    }

   TreeNode<T>* setRoot(TreeNode<T>* inputNode) {

     tempNodeRoot = inputNode;

   }

};


// do not edit below this line

#endif
