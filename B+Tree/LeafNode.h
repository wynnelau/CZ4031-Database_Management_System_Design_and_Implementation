//
// Created by Akshit Karanam on 21/9/22.
//

#ifndef LEAFNODE_H
#define LEAFNODE_H
#include "Node.h"
#include <iostream>
#include <vector>
#include "AddressNode.h"

using namespace std;

class LeafNode : public Node
{

private:
    vector<AddressNode*> addressNodes;
    LeafNode *next{};

public:
    LeafNode();
    vector<AddressNode*> getAddressNodes();
    AddressNode* getAddressNode(int index);
    int addRecordAndKey(int key, AddressNode* addressNode);
    void addRecordToExistingLeafKey(int index, Address* address);
    LeafNode *getNext();
    void setNext(LeafNode *sibling);
    void deleteRecord(int index);
    void deleteRecords();
    bool getIsLeaf();
    Node * getParent(Node *root);
};

#endif