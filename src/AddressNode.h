//
// Created by Akshit Karanam on 29/9/22.
//

#ifndef CZ4031_PROJECT1_ADDRESSNODE_H
#define CZ4031_PROJECT1_ADDRESSNODE_H

#include "Address.h"
#include <iostream>
#include <vector>

using namespace std;
class AddressNode {

private:
    vector<Address*> addresses;
public:
    vector<Address*> getAddresses();

    AddressNode();

    void addAddress(Address* address);
    void removeAddress(Address* address);
    void deleteAllAddress();
};


#endif //CZ4031_PROJECT1_ADDRESSNODE_H