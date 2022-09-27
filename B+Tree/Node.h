//
// Created by Akshit Karanam on 21/9/22.
//
using namespace std;

#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>

class Node
{

private:
    bool isLeaf;
    bool isRoot;
    vector<int> keys;
    Node *parent;
    vector<Node *> children;

public:

    //Constructor
    Node();

    // Basic get and set methods for isLeaf and isRoot
    bool getIsLeaf();
    void setIsLeaf(bool isLeafy);
    bool getIsRoot();
    void setIsRoot(bool isRooty);
    vector<int> getKeys();
    int getKey(int index); //gets key given the index (i.e index = 1, gets the second key in the node)
    void deleteAllKeys(); // deletes all the keys. i.e. clears the list
    void deleteKey(int index); //deletes key given index
    int addKey(int key); //adds a new key and sorts such that its in ascending order.
    int findSmallestKey(); //gets the smallest leaf key of that node. i.e (parentnode (5) -> leafnode(1,2,3) : returns 1)
    void deleteNode();

    // Parent
    Node *getParent();
    void setParent(Node *newParentToSet);

    // Children
    vector<Node *> getChildren();
    Node *getChild(int index);
    int addChild(Node *child); //Add child and also ensure the structure of B+ Tree holds

    // Useful for Delete Operation
    void deleteChild(Node *child);
    void deleteChildren();
    Node *getChildBefore(Node *node);
    Node *getChildAfter(Node *node);
    void addChild(Node *child, int index);
};

#endif
