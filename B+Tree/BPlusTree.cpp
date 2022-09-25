//
// Created by Akshit Karanam on 21/9/22.
//

#include "BPlusTree.h"
#include "cmath"

BPlusTree::BPlusTree(int blockSize)
{
    maxKeys = (int)(blockSize - size_pointer) / (size_key + size_pointer);
    parentMinKeys = (int)floor(maxKeys / 2);
    leafMinKeys = (int)floor((maxKeys + 1) / 2);
    root = createFirst();
    nodeCount = 0;
    deletedCount = 0;

    cout << "Max keys: " + to_string(maxKeys) + "\n";
    cout << "Parent Min Keys: " + to_string(parentMinKeys) + "\n";
    cout << "Leaf Min Keys: " + to_string(leafMinKeys) + "\n";
}

LeafNode *BPlusTree::createFirst()
{
    //    cout<<"in constructor of b+tree";
    LeafNode *newRoot = new LeafNode();
    //    cout<<newRoot->getIsLeaf();
    newRoot->setIsRoot(true);
    height = 1;
    nodeCount = 1;
    return newRoot;
}

// searches for the lead node given the value of the key (1st Step of Insertion Process)
LeafNode *BPlusTree::getLeafNode(int key)
{

    if (root->getIsLeaf())
    {
        return (LeafNode *)root;
    }

    Node *parentNode = root;
    vector<int> parentKeys;

    // Gets the relevant parent node of that required leaf node.

    while (!parentNode->getChildren().empty() && !parentNode->getChild(0)->getIsLeaf())
    {
        parentKeys = parentNode->getKeys();
        for (int i = parentKeys.size() - 1; i >= 0; i--)
        {

            if (parentKeys.at(i) <= key)
            {
                parentNode = parentNode->getChild(i + 1);
                break;
            }
            else if (i == 0)
                parentNode = parentNode->getChild(0);
        }
    }

    // Find the required LeafNode given its parent node
    parentKeys = parentNode->getKeys();

    if (!parentNode->getChildren().empty())
    {
        for (int i = parentKeys.size() - 1; i >= 0; i--)
        {

            if (parentKeys.at(i) <= key)
                return (LeafNode *)parentNode->getChild(i + 1);
        }
        return (LeafNode *)parentNode->getChild(0);
    }

    else
    {
        return (LeafNode *)parentNode;
    }
}

void BPlusTree::insert(int key, Address *address)
{

    LeafNode *relevantLeafNode = getLeafNode(key);

    for (int i = 0; i < relevantLeafNode->getKeys().size(); i++)
    {
        if (relevantLeafNode->getKeys().at(i) == key)
        {
            relevantLeafNode->addRecord(i, address);
            return;
        }
    }

    vector<Address *> addressListToAdd;
    addressListToAdd.push_back(address);

    if (relevantLeafNode->getKeys().size() < maxKeys)
    {
        if (key == 19)
        {
            cout << "reached here";
        }
        relevantLeafNode->addRecordAndKey(key, addressListToAdd);
    }
    else
    {
        splitAndInsertIntoLeaf(relevantLeafNode, key, address);
    }
}

void BPlusTree::splitAndInsertIntoLeaf(LeafNode *first, int keyToBeInserted, Address *addressToBeInserted)
{

    vector<int> keys;
    vector<vector<Address *>> addresses;
    vector<Address *> addressListToBeInserted;
    LeafNode *second = new LeafNode();
    int i;

    // Getting keys and addresses to the current node that has to be split up
    for (i = 0; i < maxKeys; i++)
    {
        keys.push_back(first->getKey(i));
        addresses.push_back(first->getRecord(i));
    }

    // sort in numerical order
    keys.push_back(keyToBeInserted);
    addressListToBeInserted.push_back(addressToBeInserted);
    addresses.push_back(addressListToBeInserted);
    for (i = keys.size() - 2; i >= 0; i--)
    {
        if (keys.at(i) <= keyToBeInserted)
        {
            i++;
            keys.at(i) = keyToBeInserted;
            addresses.at(i) = addressListToBeInserted;
            break;
        }

        keys.at(i + 1) = keys.at(i);
        addresses.at(i + 1) = addresses.at(i);

        if (i == 0)
        {
            keys.at(i) = keyToBeInserted;
            addresses.at(i) = addressListToBeInserted;
            break;
        }
    }

    // clearing old keys/addresses
    first->deleteAllKeys();
    first->deleteRecords();

    // adding (minLeafKeys) number of keys into the first node
    for (i = 0; i < leafMinKeys; i++)
    {
        first->addRecordAndKey(keys.at(i), addresses.at(i));
    }

    // adding the remaining number of keys into the second node
    for (i = leafMinKeys; i < maxKeys + 1; i++)
    {
        second->addRecordAndKey(keys.at(i), addresses.at(i));
    }

    second->setNext(first->getNext());
    first->setNext(second);

    // if the node that is being split is a root node
    if (first->getIsRoot())
    {
        Node *newRootNode = new Node();
        first->setIsRoot(false);
        newRootNode->setIsRoot(true);
        newRootNode->addChild(first);
        newRootNode->addChild(second);
        root = newRootNode;
        height++;
    }
    else if (first->getParent()->getKeys().size() < maxKeys)
    {
        first->getParent()->addChild(second);
    }
    else
    {
        splitParent(first->getParent(), second);
    }
    nodeCount++;
}

// split parent until a parent is found that is not needed to be split
void BPlusTree::splitParent(Node *parent1, Node *child)
{

    vector<Node *> children;
    vector<int> keys;
    int childSmallestKey = child->findSmallestKey();
    Node *parent2 = new Node();

    // getting the minimum key from each child. So, that we know we can arrange the children nodes in
    // ascending order.
    for (int i = 0; i < maxKeys + 1; i++)
    {
        children.push_back(parent1->getChild(i));
        keys.push_back(children.at(i)->findSmallestKey());
    }

    // sort in numerical order
    keys.push_back(childSmallestKey);
    children.push_back(child);
    for (int i = keys.size() - 2; i >= 0; i--)
    {
        if (keys.at(i) <= childSmallestKey)
        {
            i++;
            keys.at(i) = childSmallestKey;
            children.at(i) = child;
            break;
        }

        keys.at(i + 1) = keys.at(i);
        children.at(i + 1) = children.at(i);
        if (i == 0)
        {
            keys.at(i) = childSmallestKey;
            children.at(i) = child;
            break;
        }
    }

    // clearing old keys/children
    parent1->deleteAllKeys();
    parent1->deleteChildren();

    // adding (minLeafKeys) number of keys into the first node
    for (int i = 0; i < parentMinKeys + 2; i++)
    {
        parent1->addChild(children.at(i));
    }
    // adding (minLeafKeys) number of keys into the first node
    for (int i = parentMinKeys + 2; i < maxKeys + 2; i++)
    {
        parent2->addChild(children.at(i));
    }

    // Set parent for these new nodes

    // if original parent node is a root node
    if (parent1->getIsRoot())
    {
        Node *newParentNode = new Node();
        parent1->setIsRoot(false);
        newParentNode->setIsRoot(true);
        newParentNode->addChild(parent1);
        newParentNode->addChild(parent2);
        root = newParentNode;
        height++;
    }
    else if (parent1->getParent()->getKeys().size() < maxKeys)
    {
        parent1->getParent()->addChild(parent2);
    }
    else
    {
        // if needed to split again, recursively split again!
        splitParent(parent1->getParent(), parent2);
    }
    nodeCount++;
}

void BPlusTree::printBPlusTree()
{
    printBPlusTree(0, INT_MAX, root);
}

void BPlusTree::printBPlusTree(int level, int maxLevel, Node *curNode)
{
    if (!curNode)
    {
        curNode = root;
    }
    if (level > maxLevel)
    {
        return;
    }
    cout << "\n";
    cout << "h=" + to_string(level) + ";" << endl;

    cout << "[";
    for (int i = 0; i < curNode->getKeys().size(); i++)
    {
        cout << to_string(curNode->getKey(i)) + ",";
    }
    cout << "]";

    if (curNode->getIsLeaf())
    {
        return;
    }
    for (Node *child : curNode->getChildren())
    {
        printBPlusTree(level + 1, maxLevel, child);
    }
}

vector<Address *> BPlusTree::getRecordsWithKey(int key)
{
    cout << "\n\nGetting records with index key: " + to_string(key) << endl;
    int nodeAccess = 0;
    vector<Address *> requiredAddresses;
    Node *curNode = root;
    Node *parentNode;

    int numberOfNodesVisited = 0;
    while (!curNode->getIsLeaf())
    {
        numberOfNodesVisited++;

        if (numberOfNodesVisited <= 5)
        {
            cout << "[";
            for (int i = 0; i < curNode->getKeys().size(); i++)
            {
                cout << to_string(curNode->getKey(i)) + ",";
            }
            cout << "]" << endl;
        }

        parentNode = curNode;
        for (int i = 0; i < parentNode->getKeys().size(); i++)
        {

            if (key <= parentNode->getKey(i))
            {
                curNode = parentNode->getChild(i);
                nodeAccess++;
                break;
            }

            if (i == parentNode->getKeys().size() - 1)
            {
                curNode = parentNode->getChild(i + 1);
                nodeAccess++;
                break;
            }
        }
    }

    cout << "[";
    for (int i = 0; i < curNode->getKeys().size(); i++)
    {
        cout << to_string(curNode->getKey(i)) + ",";
    }
    cout << "]" << endl;

    LeafNode *leaf = (LeafNode *)curNode;
    vector<int> keys = leaf->getKeys();
    for (int i = 0; i < keys.size(); i++)
    {
        if (keys.at(i) == key)
        {
            requiredAddresses = leaf->getRecord(i);
        }
    }
    return requiredAddresses;
}
