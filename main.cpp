#include <iostream>
#include "B+Tree/BPlusTree.h"

int main() {

    Address x1 = Address(1,2);
    Address x2 = Address(1,3);
    Address x3 = Address(1,4);
    Address x4 = Address(2,1);
    Address x5 = Address(2,2);
    Address x6 = Address(2,3);
    Address x7 = Address(2,4);
    Address x8 = Address(3,1);
    Address x9 = Address(3,2);
    Address x10 = Address(3,3);
    Address x11 = Address(3,4);
    Address x12 = Address(3,5);
    Address x13 = Address(3,6);
    Address x14 = Address(3,7);
    Address x15 = Address(3,8);



    BPlusTree* index = new BPlusTree(40);

    index->insert(1,&x1);
    index->insert(4,&x2);
    index->insert(7,&x3);
    index->insert(10,&x4);
    index->insert(17,&x5);
    index->insert(21,&x6);
    index->insert(31,&x7);
    index->insert(25,&x8);
    index->insert(19,&x9);
    index->insert(20,&x10);
    index->insert(28,&x11);
    index->insert(42,&x12);
    index->insert(3,&x13);
    index->insert(5,&x14);
    index->insert(13,&x15);
    index->insert(14,&x15);
        index->insert(29,&x15);
        index->insert(24,&x15);
        index->insert(30,&x15);
        index->insert(45,&x15);
        index->insert(56,&x15);
        index->insert(52,&x15 );
        index->insert(61,&x15);
        index->insert(49,&x15);
        index->insert(64,&x15);
        index->insert(78,&x15);
        index->insert(79,&x15);
        index->insert(83,&x15);
    index->insert(85,&x15);
    index->insert(94,&x15);
    index->insert(109,&x15);
    index->insert(75,&x15);
    index->insert(92,&x15);
    index->insert(101,&x15);
    index->insert(69,&x15);
    index->insert(97,&x15);
    index->insert(99,&x15);
    index->insert(43,&x15);
    index->insert(58,&x15);
    index->insert(62,&x15);
    index->insert(105,&x15);
    index->insert(108,&x15);
    index->insert(109,&x15);
//    index->insert(110,&x15);


//    index->insert(89,&x15);
//    index->insert(18,&x15);
//    index->insert(64,&x15);










    index->printBPlusTree();


    return 0;
}
