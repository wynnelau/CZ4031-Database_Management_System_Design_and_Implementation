//
// Created by Akshit Karanam on 21/9/22.
//

#ifndef CZ4031_MINE_BPLUSTREE_H
#define CZ4031_MINE_BPLUSTREE_H

#include "LeafNode.h"
#include "Node.h"

class BPlusTree {

    const int size_pointer  = 6;
    const int size_key = 4;
    int maxKeys;
    int parentMinKeys;
    int leafMinKeys;
    Node *root;
    int height;
    int nodeCount;
    int deletedCount;


public:
    BPlusTree(int blockSize);
    LeafNode* createFirst();
    void insertToLeaf(LeafNode* leaf, int key, Address* address);
//    void searchLeaf(int key);
    void insert(int key, Address* address);
    void splitAndInsertIntoLeaf(LeafNode* old, int key, Address* address);
    void splitParent(Node* parent, Node* child);
    LeafNode* getLeafNode(int key);
    void printBPlusTree(int level, int maxLevel,  Node* curNode);

    void printBPlusTree();
};




#endif //CZ4031_MINE_BPLUSTREE_H
