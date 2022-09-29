//
// Created by Jerome Chew on 26/9/22.
//

#include "Block.h"
#include <iostream>

using namespace std;

Block::Block(int blockNumber, int offset) : blockNumber(blockNumber), offset(offset) {}

int Block::getBlockNumber(){
    return blockNumber;
}

void Block::displayBlock(){
    cout << "Block No: " << blockNumber <<endl;
    while
}