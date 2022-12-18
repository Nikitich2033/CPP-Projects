#ifndef TREE_H
#define TREE_H

#include "treenode.h"

// TODO your code goes here:

template<typename T>
class BinarySearchTree {

private:

  unique_ptr<TreeNode<T>> root;

public:


  BinarySearchTree(){

  }

  BinarySearchTree(const BinarySearchTree& inputTree):root(inputTree.root.get()){}

  BinarySearchTree<T>& operator=(const BinarySearchTree<T>& inputTree){

    root.reset(inputTree.root.get());
    return *this;

  }



  void write(ostream& os) const
  {
    root -> write(os);
  }



  TreeNode<T>* find(T data){

        TreeNode<T>* current = root.get();

        if (current == nullptr){
            return current;
        }
        else{
            while (current != nullptr){

                if(data < current->data){
                    if(current->leftChild){
                        current = current->leftChild.get();
                    }
                    else{
                        current = nullptr;
                    }
                }
                else if( current->data < data){
                    if(current->rightChild){
                    current = current->rightChild.get();
                    }
                    else{
                        current = nullptr;
                    }
                }
                else {
                    return current;
                }
            }
            return current;
        }
    }


    TreeNode<T>* insert(T data){


         TreeNode<T>* current = root.get();

         if (current == nullptr){

             TreeNode<T>* newRoot = new TreeNode<T>(data);
             root.reset(newRoot);
             return newRoot;
             delete newRoot;

         }
         else{
             while (current != nullptr){

                 if(data < current->data){
                     if(!current->leftChild){

                     TreeNode<T>* newLeftChild = new TreeNode<T>(data);
                     current->setLeftChild(newLeftChild);

                     if((newLeftChild -> parent) -> parent != nullptr){
                       int balanceF = balanceFactor((newLeftChild -> parent) -> parent);
                       //std::cout <<"Check" <<balanceF << '\n';

                       if (balanceF == 2) {
                         //rightRotation
                       }

                       else if (balanceF == -2){
                         //left rotation
                         // if (!newLeftChild->parent->rightChild.get()->leftChild) {
                         //   /* code */
                         // }
                       }

                     }

                     return newLeftChild;

                     }
                     else{

                         current = current->leftChild.get();

                     }
                 }
                 else if( current->data < data){
                     if(!current->rightChild){

                     TreeNode<T>* newRightChild = new TreeNode<T>(data);
                     current->setRightChild(newRightChild);

                     if((newRightChild -> parent) -> parent != nullptr){
                       int balanceF = balanceFactor((newRightChild -> parent) -> parent);
                      // std::cout <<"Check" <<balanceF << '\n';

                       if (balanceF == 2) {



                       }
                       else if (balanceF == -2){
                         //left rotation
                       }

                     }

                     return newRightChild;
                     }
                     else{

                         current = current->rightChild.get();
                     }

                 }
                 else {

                     return current;
                 }
             }
             //compute the balance factor of its parent's parent

             return current;
         }



     }


  TreeNodeIterator<T> begin(){

      TreeNode<T> * newRoot = root.get();

      if (root == nullptr ) {

        return nullptr;
      }
      else {

        while(newRoot->leftChild.get() != nullptr){

          newRoot = newRoot->leftChild.get();

        }

        TreeNodeIterator<T> returnIter(newRoot);

        returnIter.setRoot(root.get());

        return returnIter;
      }
    }

  TreeNodeIterator<T> end(){

      return nullptr;

    }

    int maxDepth(){

      return root.get() -> maxDepth(root.get());

    }

    int balanceFactor(TreeNode<T>* node){

      return node -> maxDepth(node -> leftChild.get()) - node -> maxDepth(node -> rightChild.get());

    }

 };


  // do not edit below this line

  #endif
