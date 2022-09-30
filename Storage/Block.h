//
// Created by Jerome Chew on 26/9/22.
//

#ifndef BLOCK_H
#define BLOCK_H
#include "Record.h"
#include <iostream>
#include <vector>

using namespace std;

class Block
{
    int maxRecords;
    int curRecords;
    vector<Record> records;

public:
    Block();
    Block(int blockSize, int blockNumber);
    int number;
    void displayBlock();
    int insertRecord(Record record);
    bool deleteRecord(int offset);
    bool getAvailableSpace();

    Record *getRecord(int offset);

    int getNumber();
};


// block: can hold 20 records
// total number of blocks: 2,500,000
#endif