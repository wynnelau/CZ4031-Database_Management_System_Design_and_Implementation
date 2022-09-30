#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;

#include "B+Tree/BPlusTree.h"
#include "Storage/Record.h"
#include "Storage/Storage.h"

static Storage *storage;
static BPlusTree *indexTree;

void *experiment1And2(int blockSize) {
    cout << "=============================================================================" << endl;
    cout << "Starting Experiment 1 and 2" << endl;
    cout << "Adding the movies data into storage and creating an index on numVotes." << endl;
    // TODO: Design the storage
    // TODO: Store the data into the disk


    storage = new Storage(150000000, 100);
    indexTree = new BPlusTree(100);

    string line;
    ifstream filename("../data/data.tsv");
    filename.ignore(10000, '\n');
    vector<Record> recordsInserted;
    vector<Address *> addressesInserted;


    int i = 0; // for testing purposes
    while (getline(filename, line)) {
//        cout << line << endl;

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

        Address* addressNeeded = storage->insertRecord(record);
        indexTree->insert(record.numVotes, addressNeeded);
    }


    // TODO: Get the number of blocks used
    // TODO: Get the size of the database (in MB)
    // TODO: While reading the data file, can also create the index on "numVotes"
    indexTree->getBPlusTreeStats();
}

void experiment3(BPlusTree *index) {
    cout << "=============================================================================" << endl;
    cout << "\nStarting Experiment 3" << endl;
    vector<Address *> addresses = index->getRecordsWithKey(500);
    // TODO: Get the number and contents of the data blocks (show the first 5).
    float numRecords = addresses.size();
    float avgRating = 0;
    for(Address* address: addresses){
        avgRating += storage->getRecord(*address)->averageRating;
    }
    avgRating /= numRecords;
    cout<<"Average Rating : " <<avgRating<<endl;

}

void experiment4(BPlusTree *index) {
    cout << "\n=============================================================================" << endl;
    cout << "Starting Experiment 4" << endl;
    vector<Address *> addresses = index->getRecordsWithRange(30000, 40000);
    // TODO: Get the number and contents of the data blocks (show the first 5).
    float numRecords = addresses.size();
    float avgRating = 0;
    for(Address* address: addresses){
        avgRating += storage->getRecord(*address)->averageRating;
    }
    avgRating /= numRecords;
    cout<<"Average Rating : " <<avgRating<<endl;
}

void experiment5(BPlusTree *index) {
    cout << "\n=============================================================================" << endl;
    cout << "Starting Experiment 5" << endl;
    vector<Address *> addressesToBeDeleted = index->deleteKey(1000);
    index->getBPlusTreeStats();
    cout << "Number of nodes deleted: " + to_string(index->getDeletedCount()) << endl;
    // TODO: DELETE Records that have address of that key from Storage.
}

// LAST STEP
// TODO: Create a basic interface to choose from either block size of 100 and block size of 500

int main() {
    experiment1And2(100);
    experiment3(indexTree);
    experiment4(indexTree);
    experiment5(indexTree);
}