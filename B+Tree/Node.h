//
// Created by Akshit Karanam on 21/9/22.
//
using namespace std;

#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
//#include <InternalNode.h>

class Node
{
private:
    vector<int> keys;
public:
    // Constructor
    Node();

    vector<int> getKeys();
    int getKey(int index);     // gets key given the index (i.e index = 1, gets the second key in the node)
    void deleteAllKeys();      // deletes all the keys. i.e. clears the list
    void deleteKey(int index); // deletes key given index
    int addKey(int key);       // adds a new key and sorts such that its in ascending order.
    void deleteNode(Node* root);
    // ABSTRACT METHODS THAT ARE OVERRIDDEN FOR CHILD CLASSES
    int virtual findSmallestKey();
    bool virtual getIsLeaf();
    Node virtual *getParent(Node* root);// gets the smallest leaf key of that node. i.e (parentnode (5) -> leafnode(1,2,3) : returns 1)
};

#endif
