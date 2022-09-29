//
// Created by Akshit Karanam on 29/9/22.
//

#ifndef CZ4031_PROJECT1_PARENTNODE_H
#define CZ4031_PROJECT1_PARENTNODE_H

#include "Node.h"

class ParentNode : public Node {
private:
    vector<Node *> children;

public:

    // Children
    vector<Node *> getChildren();
    Node *getChild(int index);
    int addChild(Node *child); // Add child and also ensure the structure of B+ Tree holds

    // Useful for Delete Operation
    void deleteChild(Node *child);
    void deleteChildren();
    Node *getChildBefore(Node *node);
    Node *getChildAfter(Node *node);
    int findSmallestKey();
    bool getIsLeaf();
    Node *getParent(Node *root);
};


#endif //CZ4031_PROJECT1_PARENTNODE_H
