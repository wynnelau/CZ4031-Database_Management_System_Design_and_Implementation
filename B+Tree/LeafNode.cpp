//
// Created by Akshit Karanam on 21/9/22.
//

#include "LeafNode.h"
#include "InternalNode.h"

LeafNode::LeafNode(){

}

vector<AddressNode*> LeafNode::getAddressNodes()
{
    return addressNodes;
}

AddressNode* LeafNode::getAddressNode(int index)
{
    return addressNodes.at(index);
}

void LeafNode::addRecordToExistingLeafKey(int index, Address *address)
{
    addressNodes.at(index)->addAddress(address);
}

int LeafNode::addRecordAndKey(int key, AddressNode* addressNode)
{

    if (addressNodes.empty())
    {
        addressNodes.push_back(addressNode);
        addKey(key);
        return 0;
    }
    int index;
    index = addKey(key);
    addressNodes.push_back(addressNode);
    for (int i = addressNodes.size() - 2; i >= index; i--)
        addressNodes.at(i + 1) = addressNodes.at(i);

    addressNodes.at(index) = addressNode;
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
    addressNodes.erase(addressNodes.begin() + index);
}

void LeafNode::deleteRecords()
{
    addressNodes.clear();
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