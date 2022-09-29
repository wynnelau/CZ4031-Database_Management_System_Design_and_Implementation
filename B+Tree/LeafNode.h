//
// Created by Akshit Karanam on 21/9/22.
//

#ifndef LEAFNODE_H
#define LEAFNODE_H
#include "Node.h"
#include "../Address.h"
#include <iostream>
#include <vector>

using namespace std;

class LeafNode : public Node
{

private:
    vector<vector<Address *>> records;
    LeafNode *next{};

public:
    LeafNode();
    vector<vector<Address *>> getRecords();
    vector<Address *> getRecord(int index);
    int addRecordAndKey(int key, vector<Address *> address);
    void addRecordToExistingLeafKey(int index, Address *address);
    LeafNode *getNext();
    void setNext(LeafNode *sibling);
    void deleteRecord(int index);
    void deleteRecords();
    bool getIsLeaf();
    Node * getParent(Node *root);
};

#endif
