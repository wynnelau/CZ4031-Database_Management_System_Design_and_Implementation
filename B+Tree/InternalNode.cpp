//
// Created by Akshit Karanam on 29/9/22.
//

#include "InternalNode.h"

// children functions
vector<Node *> InternalNode::getChildren() {
    return children;
}

Node *InternalNode::getChild(int index) {
    return children.at(index);
}

// add child to the node, and rearrange the pointers if needed.
int InternalNode::addChild(Node *child) {
    if (children.empty()) {
        children.push_back(child);
        return 0;
    }

    int key = child->findSmallestKey();
    int smallest = this->findSmallestKey();
    int index;

    if (key < smallest) { //&& !isRoot
        this->addKey(smallest);
        children.insert(children.begin() + 0, child);
        index = 0;
    } else {
        index = addKey(key);
        children.insert(children.begin() + index + 1, child);
    }
    return index;
}



void InternalNode::deleteChild(Node *child) {
    children.erase(std::remove(children.begin(), children.end(), child), children.end());
    deleteAllKeys();

    int childrenSize = children.size();
    for (int i = 0; i < childrenSize; i++) {
        if (i != 0) {

            InternalNode *node = (InternalNode *) (children.at(i));
            addKey(node->findSmallestKey());

        }


    }
}

void InternalNode::deleteChildren() {
    children.clear();
}

Node *InternalNode::getChildBefore(Node *node) {
    auto it = find(children.begin(), children.end(), node);

    // If element was found
    if (it != children.end()) {
        int index = it - children.begin();
        if (index != 0) {
            return (children.at(index - 1));
        }
    }
    return nullptr;
}

Node *InternalNode::getChildAfter(Node *node) {
    auto it = find(children.begin(), children.end(), node);

    // If element was found
    if (it != children.end()) {
        int index = it - children.begin();
        if (index != children.size() - 1) {
            return (children.at(index + 1));
        }
    }
    return nullptr;
}

int InternalNode::findSmallestKey() {

    InternalNode *copy;
    copy = this;

    while (!copy->getChild(0)->getIsLeaf()) {
        copy = (InternalNode *) copy->getChild(0);
    }

    return copy->getChild(0)->getKey(0);
}

bool InternalNode::getIsLeaf() {
    return false;
}

Node *InternalNode::getParent(Node *root) {

    InternalNode *cursor = (InternalNode *) root;
    vector<int> cursorKeys;
    int smallestKeyOfThisNode = this->findSmallestKey();

    // this is already rootNode
    if (this == cursor) {
        return nullptr;
    }

    while (!cursor->getIsLeaf()) {
        cursorKeys = cursor->getKeys();
        for (int i = cursorKeys.size() - 1; i >= 0; i--)

            if (cursorKeys.at(i) <= smallestKeyOfThisNode) {
                if ((Node *) cursor->getChild(i + 1) == this) {
                    return cursor;
                }
                cursor = (InternalNode *) cursor->getChild(i + 1);
                break;
            } else if (i == 0) {
                if ((Node *) cursor->getChild(0) == this) {
                    return cursor;
                }
                cursor = (InternalNode *) cursor->getChild(0);
            }

    }

    return cursor;

}







