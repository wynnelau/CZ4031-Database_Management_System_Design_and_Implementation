//
// Created by Jerome Chew on 26/9/22.
//

#include "Record.h"
#include <string.h>
#include <iostream>

using namespace std;

Record::Record(char tconst[10], float averageRating, int numVotes){
    strcpy(tconst,tconst);
    averageRating = averageRating;
    numVotes = numVotes;
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

void Record::displayRecord(){
    cout << "tconst :" << *tconst << "averageRating : " << averageRating << "numVotes : " << numVotes << endl;
}