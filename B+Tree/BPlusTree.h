//
// Created by Akshit Karanam on 21/9/22.
//

#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include "LeafNode.h"
#include "InternalNode.h"

class BPlusTree
{

    const int size_pointer = 6;
    const int size_key = 4;
    int maxKeys;
    int parentMinKeys;
    int leafMinKeys;
    Node *root;
    int height;
    int nodeCount;
    int deletedCount;

public:
    // Constructor and initialise
    BPlusTree(int blockSize);
    LeafNode *createFirst();

    // Experiment 2, Insertion and Basic Stats
    void getBPlusTreeStats();
    void insert(int key, Address *address);
    LeafNode *getLeafNode(int key);
    void splitAndInsertIntoLeaf(LeafNode *old, int key, Address *address);
    void splitParent(InternalNode *parent, InternalNode *child);

    // Experiment 3: get records with a particular key
    vector<Address *> getRecordsWithKey(int key);

    // Experiment 4: get records in a range [minKey,maxKey]
    vector<Address *> getRecordsWithRange(int minKey, int maxKey);

    // Experiment 5: Deletion
    vector<Address*> deleteKey(int key);
    void cureLeaf(LeafNode *node); // needed for merging/borrowing from leaf nodes
    void cureParent(InternalNode *parentNode);   // needed to cure parent node after updating leaf nodes
    int getDeletedCount();

    // to visualise the B+ Tree
    void printBPlusTree(int level, int maxLevel, Node *curNode);
    void printBPlusTree();
};

#endif
