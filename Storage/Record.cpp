//
// Created by Jerome Chew on 26/9/22.
//

#include "Record.h"
#include <string.h>
#include <iostream>

using namespace std;

Record::Record() {}

Record::Record(char* tconst, float averageRating, int numVotes){
    isDeleted = false;
    strcpy(this->tconst,tconst);
    this->averageRating = averageRating;
    this->numVotes = numVotes;
}

char Record::getTconst(){
    return tconst[10];
}

float Record::getAverageRating(){
    return averageRating;
}

int Record::getNumVotes(){
    return numVotes;
}

bool Record::getIsDeleted(){
    return isDeleted;
}

bool Record::setIsDeleted(bool del){
    isDeleted = del;
    return true;
}

void Record::displayRecord(){
    cout << " tconst :" << (tconst) << " averageRating : " << averageRating << " numVotes : " << numVotes << " isDeleted : " << isDeleted << endl;
}