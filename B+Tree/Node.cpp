//
// Created by Akshit Karanam on 21/9/22.
//

#include "Node.h"
#include "ParentNode.h"

Node::Node() {}

bool Node::getIsLeaf() {

    return false;
}

vector<int> Node::getKeys() {
    return keys;
}

int Node::getKey(int index) {
    return keys.at(index);
}

// add key such that the list is sorted!
int Node::addKey(int key) {
    if (keys.empty()) {
        keys.push_back(key);
        return 0;
    }

    int i;
    keys.push_back(key);
    for (i = keys.size() - 2; i >= 0; i--) {
        if (keys.at(i) <= key) {
            i++;
            keys.at(i) = key;
            break;
        }

        keys.at(i + 1) = keys.at(i);
        if (i == 0) {
            keys.at(i) = key;
            break;
        }
    }
    return i;
}

void Node::deleteAllKeys() {
    keys.clear();
}

void Node::deleteKey(int index) {
    keys.erase(keys.begin() + index);
}

// get smallest key of a node. For a non-leaf parent node, we are going to find the smallest key by
//  accessing its first leaf node.
int Node::findSmallestKey() {
    return this->getKey(0);
}

void Node::deleteNode(Node *root) {

    ParentNode *parent = (ParentNode *) getParent(root);
    delete this;
}

Node *Node::getParent(Node *root) {

    return nullptr;


}

