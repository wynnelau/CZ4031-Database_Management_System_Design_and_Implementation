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
    int blockNumber;
    vector<Record> records;

public:
    Block(int blockNumber, int offset);
    void displayBlock();

};


#endif 
