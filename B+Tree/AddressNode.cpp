//
// Created by Akshit Karanam on 29/9/22.
//

#include "AddressNode.h"

vector<Address*> AddressNode::getAddresses(){
    return addresses;
};

void AddressNode::addAddress(Address* address){
    addresses.push_back(address);
};

void AddressNode::removeAddress(Address* address){
    addresses.erase(std::remove(addresses.begin(), addresses.end(), address), addresses.end());
};

void AddressNode::deleteAllAddress(){
    addresses.clear();
    delete this;
}

AddressNode::AddressNode() {}