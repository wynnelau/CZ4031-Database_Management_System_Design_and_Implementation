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

public:
    Storage(size_t memorySize, size_t blockSize);
    bool insertRecord(Record record);
    bool deleteRecord(Address address);
};


#endif