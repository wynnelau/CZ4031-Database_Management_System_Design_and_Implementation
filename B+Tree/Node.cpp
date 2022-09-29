//
// Created by Akshit Karanam on 21/9/22.
//

#include "Node.h"

Node::Node()
{
    isLeaf = false;
    isRoot = false;
}

bool Node::getIsLeaf()
{
    return isLeaf;
}

void Node::setIsLeaf(bool isLeafy)
{
    isLeaf = isLeafy;
}

bool Node::getIsRoot()
{
    return isRoot;
}

void Node::setIsRoot(bool isRooty)
{
    isRoot = isRooty;
}

Node *Node::getParent()
{
    return parent;
}

void Node::setParent(Node *newParentToSet)
{
    parent = newParentToSet;
}

vector<int> Node::getKeys()
{
    return keys;
}

int Node::getKey(int index)
{
    return keys.at(index);
}

// add key such that the list is sorted!
int Node::addKey(int key)
{
    if (keys.empty())
    {
        keys.push_back(key);
        return 0;
    }

    int i;
    keys.push_back(key);
    for (i = keys.size() - 2; i >= 0; i--)
    {
        if (keys.at(i) <= key)
        {
            i++;
            keys.at(i) = key;
            break;
        }

        keys.at(i + 1) = keys.at(i);
        if (i == 0)
        {
            keys.at(i) = key;
            break;
        }
    }
    return i;
}

void Node::deleteAllKeys()
{
    keys.clear();
}

void Node::deleteKey(int index)
{
    keys.erase(keys.begin() + index);
}

// get smallest key of a node. For a non-leaf parent node, we are going to find the smallest key by
//  accessing its first leaf node.
int Node::findSmallestKey()
{
    int key;
    Node *copy;

    if (!this->getIsLeaf())
    {

        copy = this;

        while (!copy->getChild(0)->getIsLeaf())
            copy = copy->getChild(0);
        key = copy->getChild(0)->getKey(0);
    }
    else
        key = this->getKey(0);
    return key;
}

void Node::deleteNode()
{
    if (parent)
    {
        parent->deleteChild(this);
    }
    delete this;
}

// children functions
vector<Node *> Node::getChildren()
{
    return children;
}

Node *Node::getChild(int index)
{
    return children.at(index);
}

// add child to the node, and rearrange the pointers if needed.
int Node::addChild(Node *child)
{
    if (children.empty())
    {
        children.push_back(child);
        child->parent = this;
        return 0;
    }

    int key = child->findSmallestKey();
    int smallest = this->findSmallestKey();
    int index;

    child->parent = this;

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
void Node::addChild(Node *child, int index)
{
    children.insert(children.begin() + 0, child);
    child->setParent(this);
    deleteAllKeys();
    for (int i = 0; i < children.size(); i++)
    {
        if (i != 0)
        {
            addKey(children.at(i)->findSmallestKey());
        }
    }
}

void Node::deleteChild(Node *child)
{
    children.erase(std::remove(children.begin(), children.end(), child), children.end());
    deleteAllKeys();
    for (int i = 0; i < children.size(); i++)
    {
        if (i != 0)
            addKey(children.at(i)->findSmallestKey());
    }
}

void Node::deleteChildren()
{
    children.clear();
}

Node *Node::getChildBefore(Node *node)
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

Node *Node::getChildAfter(Node *node)
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
