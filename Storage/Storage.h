//
// Created by Jerome Chew on 26/9/22.
//

#ifndef STORAGE_H
#define STORAGE_H
#include "Record.h"
#include "Block.h"
#include <iostream>
#include <vector>

using namespace std;


class Storage {
    int blockSize;
    int memorySize;
    vector<Block> blocks;

public:
    Storage(size_t memorySize, size_t blockSize);
};


#endif 