//
// Created by Akshit Karanam on 21/9/22.
//

#include "BPlusTree.h"
#include "cmath"

// For sorting Address vector while querying
bool comparator(Address *a, Address *b)
{
    return b->getBlockNumber() > a->getBlockNumber();
}

BPlusTree::BPlusTree(int blockSize)
{
    maxKeys = (int)(blockSize - size_pointer) / (size_key + size_pointer);
    parentMinKeys = (int)floor(maxKeys / 2);
    leafMinKeys = (int)floor((maxKeys + 1) / 2);
    root = createFirst();
    nodeCount = 0;
    deletedCount = 0;
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

// EXPERIMENT 2: Insertion

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
            relevantLeafNode->addRecordToExistingLeafKey(i, address);
            return;
        }
    }

    vector<Address *> addressListToAdd;
    addressListToAdd.push_back(address);

    if (relevantLeafNode->getKeys().size() < maxKeys)
    {
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

// For Experiment 2
void BPlusTree::getBPlusTreeStats()
{
    cout << "\nTree statistics: " << endl;
    cout << "Max Keys in an index node (n): " + to_string(maxKeys) << endl;
    cout << "Number of nodes in B+Tree: " + to_string(nodeCount) << endl;
    cout << "Height of B+Tree: " + to_string(height) << endl;
    cout << "Content of root node: ";
    cout << "[";
    for (int i = 0; i < root->getKeys().size(); i++)
    {
        cout << to_string(root->getKey(i)) + ",";
    }
    cout << "]" << endl;
    cout << "Content of first child node: ";
    cout << "[";
    for (int i = 0; i < root->getChild(0)->getKeys().size(); i++)
    {
        cout << to_string(root->getChild(0)->getKey(i)) + ",";
    }
    cout << "]" << endl;
}

// FOR EXPERIMENT 3
vector<Address *> BPlusTree::getRecordsWithKey(int key)
{
    cout << "Getting records with index key: " + to_string(key) << endl;
    cout << "Index nodes visited: " << endl;

    int nodeAccess = 1; // starting from root
    vector<Address *> requiredAddresses;
    Node *curNode = root;
    Node *parentNode;

    while (!curNode->getIsLeaf())
    {

        if (nodeAccess <= 5)
        {
            cout << to_string(nodeAccess) + ": ";
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

    cout << to_string(nodeAccess) + ": ";
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

    cout << "Total number of index nodes visited: " + to_string(nodeAccess) << endl;
    std::sort(requiredAddresses.begin(), requiredAddresses.end(), comparator);
    return requiredAddresses;
}

// For experiment 4

vector<Address *> BPlusTree::getRecordsWithRange(int minKey, int maxKey)
{

    cout << "Getting records index key in the range: [" + to_string(minKey) + "," + to_string(maxKey) + "]"
         << endl;
    cout << "Index nodes visited: " << endl;

    int nodeAccess = 0;
    vector<Address *> requiredAddresses;
    Node *curNode = root;
    Node *parentNode;

    while (!curNode->getIsLeaf())
    {

        if (nodeAccess <= 5)
        {
            cout << to_string(nodeAccess) + ": ";
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

            if (minKey <= parentNode->getKey(i))
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

    LeafNode *leafNode = (LeafNode *)curNode;
    bool completed = false;
    while (!completed && leafNode)
    {
        nodeAccess++;

        if (nodeAccess <= 5)
        {
            cout << to_string(nodeAccess) + ": ";
            cout << "[";
            for (int i = 0; i < leafNode->getKeys().size(); i++)
            {
                cout << to_string(leafNode->getKey(i)) + ",";
            }
            cout << "]" << endl;
        }

        vector<int> keys = leafNode->getKeys();
        for (int i = 0; i < keys.size(); i++)
        {
            if (keys.at(i) >= maxKey)
            {
                completed = true;
                break;
            }
            if (keys.at(i) >= minKey)
            {
                for (Address *add : leafNode->getRecord(i))
                {
                    requiredAddresses.push_back(add);
                }
            }
        }
        leafNode = leafNode->getNext();
    }
    cout << "Total number of index nodes visited: " + to_string(nodeAccess) << endl;
    std::sort(requiredAddresses.begin(), requiredAddresses.end(), comparator);
    return requiredAddresses;
}

// Experiment 5: Deletion

void BPlusTree::deleteKey(int key)
{

    LeafNode *requiredLeafNode = getLeafNode(key);
    vector<int> keysOfLeafNode = requiredLeafNode->getKeys();

    int index = INT_MAX;
    for (int i = 0; i < keysOfLeafNode.size(); i++)
    {
        if (keysOfLeafNode.at(i) == key)
        {
            index = i;
        }
    }

    if (index == INT_MAX)
    {
        cout << "No such key exists in B+ Tree!" << endl;
        return;
    }
    bool nonLeafNodeContainsKey = false;

    Node *temp = (Node *)requiredLeafNode->getParent();

    while (temp)
    {
        vector<int> keys = temp->getKeys();
        for (int tempKey : keys)
        {
            if (tempKey == key)
            {
                nonLeafNodeContainsKey = true;
                break;
            }
        }
        temp = temp->getParent();
    }

    cout << nonLeafNodeContainsKey;

    // Simplest Case
    if (!nonLeafNodeContainsKey && requiredLeafNode->getKeys().size() - 1 >= leafMinKeys)
    {
        requiredLeafNode->deleteRecord(index); // No need to do anything else
        return;
    }

    if (requiredLeafNode->getKeys().size() - 1 < leafMinKeys)
    {
        Node *parentNode = requiredLeafNode->getParent();
        requiredLeafNode->deleteRecord(index);
        cureLeaf(requiredLeafNode);
        cureParent(parentNode);
        return;
    }
    else
    {
        Node *parentNode = requiredLeafNode->getParent();
        requiredLeafNode->deleteRecord(index);
        cureParent(parentNode);
    }
}

void BPlusTree::cureParent(Node *parentNode)
{

    int minimumNumberOfChildren = parentMinKeys + 1;
    Node *newParentNode;

    // if parentNode is rootNode // also the termination condition for this recursive function.
    if (parentNode->getIsRoot())
    {

        // root node has more than 1 child
        if (parentNode->getChildren().size() > 1)
        {
            // So you are just curing the node, such that they have the updated key values.
            Node *child = parentNode->getChild(0);
            // In this delete child process, the keys are also updated accordingly to the other remaining children
            // check the Node.deleteChild() method for better understanding
            parentNode->deleteChild(child);
            // Adding back the initially deleted child.
            parentNode->addChild(child);
            return;
        }

        // during the deletion process, there are times when the root has only left with 1 child.
        if (parentNode->getChildren().size() == 1)
        {
            parentNode->getChild(0)->setIsRoot(true);
            root = parentNode->getChild(0);
            parentNode->deleteNode();
            deletedCount++;
            height--;
            return;
        }
    }

    if (parentNode->getChildren().size() >= minimumNumberOfChildren)
    {
        Node *child = parentNode->getChild(0);
        parentNode->deleteChild(child);
        parentNode->addChild(child);
        newParentNode = parentNode->getParent();
    }

    // borrow or merge from neighbours!
    else
    {

        Node *before = parentNode->getParent()->getChildBefore(parentNode);
        Node *after = parentNode->getParent()->getChildAfter(parentNode);

        int numberOfKeysSpareB = 0;
        int numberOfKeysSpareA = 0;

        // get the min number of keys that are required to cure the node

        if (after)
        {
            numberOfKeysSpareA = after->getKeys().size() - parentMinKeys;
        }

        if (before)
        {
            numberOfKeysSpareB = before->getKeys().size() - parentMinKeys;
        }

        // can borrow from siblings (default: borrows from after if possible.)
        if (numberOfKeysSpareA >= 1 || numberOfKeysSpareB >= 1)
        {

            if (numberOfKeysSpareA >= 1)
            {
                Node *childNeededToMove = after->getChild(0);
                parentNode->addChild(childNeededToMove);
                after->deleteChild(childNeededToMove);
            }
            else
            {
                Node *childNeededToMove = before->getChild(0);
                parentNode->addChild(childNeededToMove);
                before->deleteChild(childNeededToMove);
            }
            newParentNode = parentNode->getParent();
        }
        // Merge 2 parent nodes
        else
        {
            if (after)
            {
                for (int i = 0; i < parentNode->getChildren().size(); i++)
                {
                    after->addChild(parentNode->getChild(i));
                }
            }
            else
            {
                for (int i = 0; i < parentNode->getChildren().size(); i++)
                {
                    before->addChild(parentNode->getChild(i));
                }
            }
            newParentNode = parentNode->getParent();
            parentNode->deleteNode();
            deletedCount++;
        }
    }
    cureParent(newParentNode);
}

void BPlusTree::cureLeaf(LeafNode *leaf)
{
    int initialNumberOfKeys = leaf->getKeys().size();
    Node *copy = leaf;

    // There is no need to cure the LeafNode (i.e Borrow/Merge)
    if (initialNumberOfKeys >= leafMinKeys)
    {
        return;
    }

    LeafNode *before = (LeafNode *)leaf->getParent()->getChildBefore(leaf);
    LeafNode *after = (LeafNode *)leaf->getParent()->getChildAfter(leaf);

    int numberOfKeysSpareB = 0;
    int numberOfKeysSpareA = 0;

    // get the min number of keys that are required to cure the node

    if (after)
    {
        numberOfKeysSpareA = after->getKeys().size() - leafMinKeys;
    }

    if (before)
    {
        numberOfKeysSpareB = before->getKeys().size() - leafMinKeys;
    }

    // can borrow from siblings (default: borrows from after if possible.)
    if (numberOfKeysSpareA >= 1 || numberOfKeysSpareB >= 1)
    {

        if (numberOfKeysSpareA >= 1)
        {
            leaf->addRecordAndKey(after->getKey(after->getKeys().size() - 1),
                                  after->getRecord(after->getKeys().size() - 1));
            after->deleteRecord(after->getKeys().size() - 1);
        }
        else
        {
            leaf->addRecordAndKey(before->getKey(before->getKeys().size() - 1),
                                  before->getRecord(after->getKeys().size() - 1));
            after->deleteRecord(before->getKeys().size() - 1);
        }
    }

    // cannot borrow from siblings, need to merge
    else
    {
        if (after)
        {
            for (int i = 0; i < leaf->getKeys().size(); i++)
            {
                after->addRecordAndKey(leaf->getKey(i), leaf->getRecord(i));
            }
        }
        else
        {
            for (int i = 0; i < leaf->getKeys().size(); i++)
            {
                before->addRecordAndKey(leaf->getKey(i), leaf->getRecord(i));
            }
        }

        if (!before)
        {
            if (!copy->getIsRoot())
            {
                int keyToFind;
                if (copy->findSmallestKey() - (maxKeys + 1) > 0)
                {
                    keyToFind = copy->findSmallestKey() - (maxKeys + 1);
                }
                else
                {
                    keyToFind = 0;
                }
                before = getLeafNode(keyToFind);
            }
        }

        before->setNext(leaf->getNext());
        leaf->deleteNode();
        deletedCount++;
    }
}
