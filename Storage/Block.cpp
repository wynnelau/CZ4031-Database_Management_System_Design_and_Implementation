//
// Created by Jerome Chew on 26/9/22.
//

#include "Block.h"
#include "Record.h"
#include <iostream>
#include <vector>

using namespace std;

Block::Block(int blockSize) {

    maxRecords = blockSize / sizeof(Record);
    curRecords = 0;
    vector<Record> records = vector<Record>(maxRecords);
}

void Block::displayBlock() {
    for (int i = 0; i <= records.size() - 1; i++) {
        if (!records.at(i).getIsDeleted()) {
            cout << "Record " << i;
            records.at(i).displayRecord();
        }
    }
}

int Block::insertRecord(Record record) {
    // Block is full
    if (curRecords == maxRecords) {
        return 0;
    }
    if(records.empty()){
        records.push_back((record));
        curRecords++;
        return 0;
    }

    // Insert record at the deleted index
    for (int i = 0; i <= records.size() - 1; i++) {
        if (records.at(i).getIsDeleted()) {
            records.at(i) = record;
            curRecords++;
            return i;
        }
    }

    records.push_back(record);
    curRecords++;
    return records.size()-1;
}

bool Block::deleteRecord(int offset) {
    if (offset > curRecords) return false;
    records.at(offset).setIsDeleted(true);
    curRecords--;
    return true;
}

Record* Block::getRecord(int offset) {
    if (offset > curRecords) return nullptr;
    return &(records.at(offset));
}

bool Block::getAvailableSpace() {
    if (curRecords < maxRecords) {
        return true;
    } else return false;
}

Block::Block() {}

