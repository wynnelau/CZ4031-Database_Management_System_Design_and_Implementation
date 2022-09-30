//
// Created by Jerome Chew on 26/9/22.
//

#include "Block.h"
#include "Record.h"
#include <iostream>
#include <vector>

using namespace std;

Block::Block(int blockSize){
    maxRecords = blockSize/sizeof(Record);
    curRecords = 0;
    vector<Record> records = vector<Record> (maxRecords);
}

void Block::displayBlock(){
    for(int i =1; i<=curRecords; i++){
        if (!records.at(i-1).getIsDeleted()){
            cout << "Record " << i ;
            records.at(i-1).displayRecord();}
    }
}

bool Block::insertRecord(Record record){
    // Block is full
    if(curRecords == maxRecords){
        return false;
    }
    // Insert record at the deleted index
    for(int i =1; i<=maxRecords; i++){
        if (records.at(i-1).getIsDeleted()){
            records.at(i-1) = record;
            curRecords++;
            return true;}
    }

    records.at(curRecords) = record;
    curRecords++;
    return true;
}

bool Block::deleteRecord(int offset){
    if(offset > curRecords) return false;
    records.at(offset-1).setIsDeleted(true);
    curRecords--;
    return true;
}

bool Block::getAvailableSpace(){
    if(curRecords < maxRecords){
        return true;
    }
    else return false;
}

Block::Block() {}
