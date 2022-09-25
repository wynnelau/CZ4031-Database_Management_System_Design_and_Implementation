#include <iostream>
#include "B+Tree/BPlusTree.h"

int main()
{
    // Block Size is set to 40. so now n = 3!
    BPlusTree *index = new BPlusTree(40);
    int arr[] = {1,4,20,7,10,17,21,31,25,19,20,28,42,3,5,13,14,29,20,
    24,30,20,45,56,52,20,61,49,64,78,79,83,85,94,20,109,75,20,92,101,69,97,99
    ,43,58,62,20,105,108,109};

    for(int i =0;i< sizeof(arr)/sizeof(int);i++ ){
        index->insert(arr[i],new Address(i,1));
    }

    index->printBPlusTree();

    vector<Address*> addressesRequired = index->getRecordsWithKey(20);

    cout<<"\n";
    for(int i =0; i<addressesRequired.size();i++){
        Address* address = addressesRequired.at(i);
        cout<<  "Block No: " + to_string(address->getBlockNumber())  + ", Offset: " + to_string(address->getOffSet())<<endl;
        
    }






    return 0;
}
