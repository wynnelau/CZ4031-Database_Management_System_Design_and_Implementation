//
// Created by Akshit Karanam on 21/9/22.
//

#ifndef ADDRESS_H
#define ADDRESS_H

class Address
{
    int blockNumber;
    int offset;

public:
    Address(int blockNumber, int offset);
    int getBlockNumber();
    int getOffSet();
};

#endif
