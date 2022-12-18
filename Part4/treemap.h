#ifndef TREEMAP_H
#define TREEMAP_H

#include "tree.h"

template<typename Key, typename Value>
class KeyValuePair {

private:

public:

    const Key k;
    Value v;

    // TODO your code for KeyValuePair goes here

    KeyValuePair(Key keyIn, Value valueIn): k(keyIn),v(valueIn){}

    KeyValuePair(Key keyIn):k(keyIn){}

    bool operator<( KeyValuePair<Key,Value> keyValue){

      return(k < keyValue.k);

    }

};



template<typename Key, typename Value>
ostream & operator<< (ostream & o, const KeyValuePair<Key,Value> & keyvValuePair){
    o << keyvValuePair.k << "," << keyvValuePair.v;
    return o;
}



template<typename Key, typename Value>
class TreeMap {

private:
    BinarySearchTree<KeyValuePair<Key,Value> > tree;

public:

    KeyValuePair<Key,Value> * insert(const Key & key, const Value & value) {
        return &(tree.insert(KeyValuePair<Key,Value>(key,value))->data);
    }

    void write(ostream & o) const {
        tree.write(o);
    }

    // TODO your code for TreeMap goes here:

    KeyValuePair<Key,Value>* find(Key k){

       KeyValuePair<Key,Value> KeyValuePair(k);

       if (tree.find(KeyValuePair)!=nullptr){

         return &tree.find(KeyValuePair)->data;

       }
       else {

         return nullptr;

       }
   }


};


// do not edit below this line

#endif
