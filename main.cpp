#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
using namespace std;

#include "B+Tree/BPlusTree.h"

BPlusTree *experiment1And2(int blockSize)
{
    cout << "=============================================================================" << endl;
    cout << "Starting Experiment 1 and 2" << endl;
    cout << "Adding the movies data into storage and creating an index on numVotes." << endl;
    // TODO: Design the storage
    // TODO: Store the data into the disk
    string line;
    ifstream filename("../data/data.tsv");
    filename.ignore(10000,'\n');

    int i = 0; // for testing purposes
    while (getline (filename, line) && i < 3) {
        cout << line << endl;

        stringstream linestream(line);
        string row;
        char col1[10];
        float col2;
        int col3;

        getline(linestream, row, '\t');
        strcpy(col1,row.c_str());  //col1 to be placed into record
        cout << col1 << endl;
        getline(linestream, row, '\t');
        col2 = std::stof(row); //col2 to be placed into record
        cout << col2 << endl;
        getline(linestream, row, '\t');
        col3 = std::stoi(row); //col3 to be placed into record
        cout << col3 << endl;

        i++;
    }
    // TODO: Get the number of blocks used
    // TODO: Get the size of the database (in MB)
    // TODO: While reading the data file, can also create the index on "numVotes"

    // In the meantime, this can be used for testing BPlusTree (take note that only the number 20 has repetitions below.
    // There are no repeated keys in this BPlusTree implementation. There is a vector of addresses each leaf node
    // key points to.
    BPlusTree *index = new BPlusTree(40);
         int arr[] = {1,4,20,7,10,17,21,31,25,19,20,28,42,3,5,13,14,29,20,
                      24,30,20,45,56,52,20,61,49,64,78,79,83,85,94,20,109,75,20,92,101,69,97,99
                 ,43,58,62,20,105,108,109};

//    int arr[] = {1, 25, 31, 20, 21, 4, 17, 19, 7, 10, 5};

    for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
    {
        index->insert(arr[i], new Address(i, 1));
    }
    index->getBPlusTreeStats();
    index->printBPlusTree();

    return index;
}

void experiment3(BPlusTree *index)
{
    cout << "=============================================================================" << endl;
    cout << "\nStarting Experiment 3" << endl;
    vector<Address *> addresses = index->getRecordsWithKey(20);
    // TODO: using these addresses, get the records
    // TODO: Get the number and contents of the data blocks (show the first 5).
    // TODO: with the obtained records find the avgRating

    // For now, print the addresses for checking purposes.
    cout << "\n";
    for (int i = 0; i < addresses.size(); i++)
    {
        Address *address = addresses.at(i);
        cout << "Block No: " + to_string(address->getBlockNumber()) + ", Offset: " + to_string(address->getOffSet()) << endl;
    }
}

void experiment4(BPlusTree *index)
{
    cout << "\n=============================================================================" << endl;
    cout << "Starting Experiment 4" << endl;
    vector<Address *> addresses = index->getRecordsWithRange(10, 30);
    // TODO: using these addresses, get the records
    // TODO: Get the number and contents of the data blocks (show the first 5).
    // TODO: with the obtained records find the avgRating

    // For now, print the addresses for checking purposes.
    cout << "\n";
    for (int i = 0; i < addresses.size(); i++)
    {
        Address *address = addresses.at(i);
        cout << "Block No: " + to_string(address->getBlockNumber()) + ", Offset: " + to_string(address->getOffSet()) << endl;
    }
}

void experiment5(BPlusTree* index)
{
    cout << "\n=============================================================================" << endl;
    cout << "Starting Experiment 4" << endl;
//    index->printBPlusTree();
    vector<Address*> addressesToBeDeleted = index->deleteKey(20);
//    index->deleteKey(19);
    index->getBPlusTreeStats();
    cout<<"Number of nodes deleted: " + to_string(index->getDeletedCount())<<endl;
    // TODO: DELETE Records that have address of that key from Storage.
}

// LAST STEP
// TODO: Create a basic interface to choose from either block size of 100 and block size of 500

int main()
{
       // Block Size is set to 40. so now n = 3!
    BPlusTree* index = experiment1And2(40);
    experiment3(index);
    experiment4(index);
    experiment5(index);
}