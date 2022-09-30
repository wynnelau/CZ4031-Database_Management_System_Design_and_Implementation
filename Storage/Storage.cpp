//
// Created by Jerome Chew on 26/9/22.
//

#include "Storage.h"
#include "Block.h"
#include <vector>

using namespace std;

Storage::Storage(size_t memorySize, size_t blockSize) {
    memorySize = memorySize;
    blockSize = blockSize;
    maxBlocks = memorySize / blockSize;
    curBlocks = 0;
    vector<Block> blocks = vector<Block> (maxBlocks);
}

bool Storage::insertRecord(Record record){
    // Storage is full
    for(int i =1; i<=curBlocks; i++){
        // Checking if blocks have available spaces (including deleted spaces)
        if (blocks.at(i-1).getAvailableSpace()){
            blocks.at(i-1).insertRecord(record);
            return true;
        }

        if(curBlocks <= maxBlocks){
            blocks.at(curBlocks) = Block(blockSize);
            blocks.at(curBlocks).insertRecord(record);
            curBlocks++;
            return true;
        }

        else{
            cout << "Storage is full!" << endl;
            return false;
        }
    }
}

bool Storage::deleteRecord(Address address){
    if(address.getBlockNumber() > maxBlocks) return false;
    blocks.at(address.getBlockNumber() -1 ).deleteRecord(address.getOffSet());
    return true;
}
