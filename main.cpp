#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>


#include <algorithm>

using namespace std;
# include "Storage/Storage.h"
#include "B+Tree/BPlusTree.h"
#include "Storage/Record.h"
#include "Storage/Block.h"


static Storage *storage;
static BPlusTree *indexTree;
void experiment1And2(int blockSize) {
    cout << "=============================================================================" << endl;
    cout << "Starting Experiment 1 and 2" << endl;
    cout << "Adding the movies data into storage and creating an index on numVotes." << endl;
    // Each record is 20 Bytes

    storage = new Storage(500000000, blockSize);
    indexTree = new BPlusTree(blockSize);

    string line;
    ifstream filename("../data/data.tsv");
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

void experiment3(BPlusTree *index) {
    cout << "=============================================================================" << endl;
    cout << "\nStarting Experiment 3" << endl;
    vector<Address *> addresses = index->getRecordsWithKey(500);
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

void experiment4(BPlusTree *index) {
    cout << "\n=============================================================================" << endl;
    cout << "Starting Experiment 4" << endl;
    vector<Address *> addresses = index->getRecordsWithRange(30000, 40000);
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

void experiment5(BPlusTree *index) {
    cout << "\n=============================================================================" << endl;
    cout << "Starting Experiment 5" << endl;
    vector<Address *> addressesToBeDeleted = index->deleteKey(1000);
    index->getBPlusTreeStats();
    cout << "Number of nodes deleted: " + to_string(index->getDeletedCount()) << endl;

    for(Address* address: addressesToBeDeleted){
        storage->deleteRecord(*address);
    }
}

// LAST STEP
// TODO: Create a basic interface to choose from either block size of 200 and block size of 500 maybe can add in a loop?

int main()
{
    while(true){
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
        experiment1And2(size);
        experiment3(indexTree);
        experiment4(indexTree);
        experiment5(indexTree);

    }

}