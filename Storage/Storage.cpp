//
// Created by Jerome Chew on 26/9/22.
//

#include "Storage.h"
#include "Block.h"
#include <vector>
#include <algorithm>

using namespace std;


Storage::Storage(size_t memorySize, size_t blockSize) {

    this->memorySize = memorySize;
    this->blockSize = blockSize;
    maxBlocks = memorySize / blockSize;
    vector<Block> blocks = vector<Block>(maxBlocks);
}

Address *Storage::insertRecord(Record record) {
    int insertedOffset = 0;

//    if (!blocksThatHaveDeletes.empty()) {
//        blocks.at(blocksThatHaveDeletes.at(0)).insertRecord(record);
//    }

    if (blocks.size() < maxBlocks) {
        Block newBlock = Block(blockSize);
        blocks.push_back(newBlock);
        blocks.at(blocks.size() - 1).insertRecord(record);
        curBlocks++;
        return new Address(curBlocks - 1, insertedOffset);
    } else {
        cout << "Storage is full!" << endl;
        return nullptr;
    }

}

bool Storage::deleteRecord(Address address) {
    if (address.getBlockNumber() > maxBlocks) return false;
    blocks.at(address.getBlockNumber()).deleteRecord(address.getOffSet());
    blocksThatHaveDeletes.push_back(address.getBlockNumber());
    std::sort(blocksThatHaveDeletes.begin(), blocksThatHaveDeletes.end());
    blocksThatHaveDeletes.erase( unique( blocksThatHaveDeletes.begin(), blocksThatHaveDeletes.end() ), blocksThatHaveDeletes.end() );
    return true;
}

Record *Storage::getRecord(Address address) {
    if (address.getBlockNumber() > maxBlocks) return nullptr;
    return blocks.at(address.getBlockNumber()).getRecord(address.getOffSet());
}


void Storage::getAllRecords() {
    for (int i = 0; i < blocks.size(); i++) {
        blocks.at(i).displayBlock();
    }

}





