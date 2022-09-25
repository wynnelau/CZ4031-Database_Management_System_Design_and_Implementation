//
// Created by Akshit Karanam on 21/9/22.
//
using namespace std;

#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>


class Node {

private:
    bool isLeaf;
    bool isRoot;
    vector<int> keys;
    Node* parent;
    vector<Node*> children;

public:

    // All these functions look good!
    Node();
    bool getIsLeaf();
    void setIsLeaf(bool isLeafy);
    bool getIsRoot();
    void setIsRoot(bool isRooty);
    vector<int> getKeys();
    int getKey(int index);
    int addKey(int key);
    void deleteKey(int index);
    void deleteAllKeys();
    int findSmallestKey();
    void deleteNode();

    //Parent
    Node* getParent();
    void setParent(Node* newParentToSet);

    //Children
    vector<Node*> getChildren();
    Node* getChild(int index);
    int addChild(Node* child);
    virtual void splitPrep();
    void deleteChild(Node* child);
    void deleteChildren();
    Node* getChildBefore(Node* node);
    Node* getChildAfter(Node* node);

    void addChild(Node *child, int index);
};



#endif 
