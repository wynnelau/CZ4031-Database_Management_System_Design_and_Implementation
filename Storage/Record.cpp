//
// Created by Jerome Chew on 26/9/22.
//

#include "Record.h"
#include <string.h>
#include <iostream>

using namespace std;

Record::Record(char tconst[10], float averageRating, int numVotes, bool isDeleted){
    strcpy(tconst,tconst); //10 bytes
    averageRating = averageRating; //4 bytes
    numVotes = numVotes; //4 bytes
    //isDeleted to indicate if record has been deleted for experiment 5
    isDeleted = false; //2 bytes
    //Total is 20 Bytes
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

bool Record::setIsDeleted(){
    isDeleted = true;
}

void Record::displayRecord(){
    cout << "tconst :" << *tconst << "averageRating : " << averageRating << "numVotes : " << numVotes << "isDeleted : " << isDeleted << endl;
}