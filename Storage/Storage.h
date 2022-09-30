//
// Created by Jerome Chew on 26/9/22.
//

#ifndef STORAGE_H
#define STORAGE_H
#include "Record.h"
#include "Block.h"
#include "Address.h"
#include <iostream>
#include <vector>

using namespace std;


class Storage {
    int blockSize;
    int memorySize;
    int maxBlocks;
    int curBlocks;
    vector<Block> blocks;
    vector<int> blocksThatHaveDeletes;


public:
    Storage(size_t memorySize, size_t blockSize);
    Address * insertRecord(Record record);
    bool deleteRecord(Address address);

    Storage();

    void getAllRecords();

    Record *getRecord(Address address);
    int getNumberOfBlocksUsed();
    float getSizeOfDatabase(int blockSize);

    Record *printBlock(int blockNum);
};


#endif