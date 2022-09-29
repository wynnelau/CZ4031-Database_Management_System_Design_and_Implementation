//
// Created by Akshit Karanam on 29/9/22.
//

#include "ParentNode.h"

// children functions
vector<Node *> ParentNode::getChildren()
{
    return children;
}

Node *ParentNode::getChild(int index)
{
    return children.at(index);
}

// add child to the node, and rearrange the pointers if needed.
int ParentNode::addChild(Node *child)
{
    if (children.empty())
    {
        children.push_back(child);
        return 0;
    }

    int key = child->findSmallestKey();
    int smallest = this->findSmallestKey();
    int index;

    if (key < smallest)
    { //&& !isRoot
        this->addKey(smallest);
        children.insert(children.begin() + 0, child);
        index = 0;
    }
    else
    {
        index = addKey(key);
        children.insert(children.begin() + index + 1, child);
    }
    return index;
}

// NOT sure why we have to use this!
void ParentNode::addChild(Node *child, int index)
{
    children.insert(children.begin() + 0, child);
    deleteAllKeys();
    for (int i = 0; i < children.size(); i++)
    {
        if (i != 0)
        {
            addKey(children.at(i)->findSmallestKey());
        }
    }
}

void ParentNode::deleteChild(Node *child)
{
    children.erase(std::remove(children.begin(), children.end(), child), children.end());
    deleteAllKeys();
    for (int i = 0; i < children.size(); i++)
    {
        if (i != 0)
            addKey(children.at(i)->findSmallestKey());
    }
}

void ParentNode::deleteChildren()
{
    children.clear();
}

Node *ParentNode::getChildBefore(Node *node)
{
    auto it = find(children.begin(), children.end(), node);

    // If element was found
    if (it != children.end())
    {
        int index = it - children.begin();
        if (index != 0)
        {
            return (children.at(index - 1));
        }
    }
    return nullptr;
}

Node *ParentNode::getChildAfter(Node *node)
{
    auto it = find(children.begin(), children.end(), node);

    // If element was found
    if (it != children.end())
    {
        int index = it - children.begin();
        if (index != children.size() - 1)
        {
            return (children.at(index + 1));
        }
    }
    return nullptr;
}

int ParentNode::findSmallestKey() {

    ParentNode* copy;
    copy = this;

    while(!copy->getChild(0)->getIsLeaf()) {
        copy = (ParentNode*) copy->getChild(0);
    }

    return copy->getChild(0)->getKey(0);
}

bool ParentNode::getIsLeaf() {
    return false;
}

Node* ParentNode::getParent(Node *root) {

    ParentNode *cursor = (ParentNode *) root;
    vector<int> cursorKeys;
    int smallestKeyOfThisNode = this->findSmallestKey();


    while (!cursor->getIsLeaf()) {
        cursorKeys = cursor->getKeys();
        for (int i = cursorKeys.size() - 1; i >= 0; i--)

            if (cursorKeys.at(i) <= smallestKeyOfThisNode) {
                if ((Node *) cursor->getChild(i + 1) == this) {
                    return cursor;
                }
                cursor = (ParentNode *) cursor->getChild(i + 1);
                break;
            } else if (i == 0) {
                if ((Node *) cursor->getChild(0) == this) {
                    return cursor;
                }
                cursor = (ParentNode *) cursor->getChild(0);
            }

    }

    return cursor;

}







