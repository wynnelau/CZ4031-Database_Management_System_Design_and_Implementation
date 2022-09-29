//
// Created by Jerome Chew on 26/9/22.
//

#ifndef BLOCK_H
#define BLOCK_H
#include "Record.h"
#include <iostream>
#include <vector>

using namespace std;


class Block {
    int maxRecords;
    int curRecords;
    vector<Record> records;

public:
    Block(int blockSize);
    void displayBlock();
    bool insertRecord(Record record);
    bool deleteRecord(int offset);
    bool getAvailableSpace();
};


#endif 
