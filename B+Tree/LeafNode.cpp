//
// Created by Akshit Karanam on 21/9/22.
//

#include "LeafNode.h"
#include "InternalNode.h"

LeafNode::LeafNode(){

}

vector<vector<Address *>> LeafNode::getRecords()
{
    return records;
}

vector<Address *> LeafNode::getRecord(int index)
{
    return records.at(index);
}

void LeafNode::addRecordToExistingLeafKey(int index, Address *address)
{
    records.at(index).push_back(address);
}

int LeafNode::addRecordAndKey(int key, vector<Address *> addresses)
{

    if (records.empty())
    {
        records.push_back(addresses);
        addKey(key);
        return 0;
    }
    int index;
    index = addKey(key);
    records.push_back(addresses);
    for (int i = records.size() - 2; i >= index; i--)
        records.at(i + 1) = records.at(i);

    records.at(index) = addresses;
    return index;
}

LeafNode *LeafNode::getNext()
{
    return next;
}

void LeafNode::setNext(LeafNode *sibling)
{
    next = sibling;
}

void LeafNode::deleteRecord(int index)
{
    deleteKey(index);
    records.erase(records.begin() + index);
}

void LeafNode::deleteRecords()
{
    records.clear();
}

bool LeafNode::getIsLeaf() {
    return true;
}

Node* LeafNode::getParent(Node *root) {

    int  key= findSmallestKey();
    if (root->getIsLeaf())
    {
        return (LeafNode *)root;
    }

    InternalNode* parentNode = (InternalNode*) root;
    vector<int> parentKeys;

    while (!parentNode->getChild(0)->getIsLeaf())
    {
        parentKeys = parentNode->getKeys();
        for (int i = parentKeys.size() - 1; i >= 0; i--)
        {

            if (parentKeys.at(i) <= key)
            {
                parentNode = (InternalNode*) parentNode->getChild(i + 1);
                break;
            }
            else if (i == 0)
                parentNode = (InternalNode*) parentNode->getChild(0);
        }
    }

    return parentNode;
}
