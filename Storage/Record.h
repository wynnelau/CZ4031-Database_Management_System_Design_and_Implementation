//
// Created by Jerome Chew on 26/9/22.
//

#ifndef RECORD_H
#define RECORD_H


class Record {
    char tconst[10];
    float averageRating;
    int numVotes;

public:
    Record(char tconst[10], float averageRating, int numVotes);
    void displayRecord();
    char getTconst();
    float getAverageRating();
    int getNumVotes();
};


#endif 
