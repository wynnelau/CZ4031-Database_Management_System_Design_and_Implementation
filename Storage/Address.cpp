//
// Created by Akshit Karanam on 21/9/22.
//

#include "Address.h"

Address::Address(int blockNumber, int offset) : blockNumber(blockNumber), offset(offset) {}

int Address::getBlockNumber(){
    return blockNumber;
}

int Address::getOffSet(){
    return offset;
}