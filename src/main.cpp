#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>


#include <algorithm>
#include "Storage.h"
#include "BPlusTree.h"
#include "Record.h"
#include "Block.h"


void experiment1And2(int blockSize, Storage* storage, BPlusTree* indexTree) {
    cout << "=============================================================================" << endl;
    cout << "Starting Experiment 1 and 2" << endl;
    cout << "Adding the movies data into storage and creating an index on numVotes." << endl;
    // Each record is 20 Bytes

    string line;
    ifstream filename("data.tsv");
    filename.ignore(10000, '\n');

    while (getline (filename, line)) {

        Record record;
        stringstream linestream(line);
        string row;

        getline(linestream, row, '\t');
        // add tconst, averageRating and numVotes into each record
        strcpy(record.tconst, row.c_str());
        getline(linestream, row, '\t');
        record.averageRating = std::stof(row);
        getline(linestream, row, '\t');
        record.numVotes = std::stoi(row);
        record.isDeleted = false;
        

        Address* addressNeeded = storage->insertRecord(record);
        indexTree->insert(record.numVotes, addressNeeded);
    }

    // print results of experiment 1
    cout<<"Number of blocks used : " <<storage->getNumberOfBlocksUsed()<<endl;
    cout<<"Size of the database (in MB) : " <<storage->getSizeOfDatabase(blockSize)<<endl;
    indexTree->getBPlusTreeStats();


}

void experiment3(Storage* storage, BPlusTree* indexTree) {
    cout << "=============================================================================" << endl;
    cout << "\nStarting Experiment 3" << endl;
    vector<Address *> addresses = indexTree->getRecordsWithKey(500);
    float numRecords = addresses.size();
    float avgRating = 0;
    int i = 1;
    cout<<"\nData Blocks accessed:"<<endl;
    for(Address* address: addresses){
        avgRating += storage->getRecord(*address)->getAverageRating();
        if(i<=5){
            storage->printBlock(address->getBlockNumber());
            i++;
        }

    }
    avgRating /= numRecords;
    cout<<"Number of Data Blocks accessed: "<<addresses.size()<<endl;
    cout<<"Average Rating : " <<avgRating<<endl;

}

void experiment4(Storage* storage, BPlusTree* indexTree) {
    cout << "\n=============================================================================" << endl;
    cout << "Starting Experiment 4" << endl;
    vector<Address *> addresses = indexTree->getRecordsWithRange(30000, 40000);
    float numRecords = addresses.size();
    float avgRating = 0;
    int i = 1;
    cout<<"\nData Blocks accessed:"<<endl;
    for(Address* address: addresses){
        avgRating += storage->getRecord(*address)->averageRating;
        if(i<=5){
            storage->printBlock(address->getBlockNumber());
            i++;
        }
    }
    avgRating /= numRecords;
    cout<<"Number of Data Blocks accessed: "<<addresses.size()<<endl;
    cout<<"Average Rating : " <<avgRating<<endl;
}

void experiment5(Storage* storage, BPlusTree* indexTree) {
    cout << "\n=============================================================================" << endl;
    cout << "Starting Experiment 5" << endl;
    vector<Address *> addressesToBeDeleted = indexTree->deleteKey(1000);
    indexTree->getBPlusTreeStats();
    cout << "Number of nodes deleted: " + to_string(indexTree->getDeletedCount()) << endl;

    for(Address* address: addressesToBeDeleted){
        storage->deleteRecord(*address);
    }
}

// LAST STEP
// TODO: Create a basic interface to choose from either block size of 200 and block size of 500 maybe can add in a loop?

int main()
{
    
    int blksize, size;
    cout << "=============================================================================" << endl;
    cout << "Choose block size (1/2) : " << endl;
    cout << "1. 200B" << endl;
    cout << "2. 500B" << endl;
    cout << "3. Quit"<<endl;
    cin >> blksize;
    switch (blksize) {
        case 1:
            cout << "Block size set to 200B" << endl;
            size = 200;
            break;
        case 2:
            cout << "Block size set to 500B" << endl;
            size = 500;
            break;
        case 3:
            cout<<"Exiting..."<<endl;
            return 0;

        default:
            cout << "Error" << endl;
            return 0;
    }

    Storage *storage = new Storage(150000000,size);
    BPlusTree *index = new BPlusTree(size);

    experiment1And2(size,storage,index);
    experiment3(storage,index);
    experiment4(storage,index);
    experiment5(storage,index);    
}