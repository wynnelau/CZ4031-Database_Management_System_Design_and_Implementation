//
// Created by Jerome Chew on 26/9/22.
//

#include "Storage.h"

using namespace std;

Storage::Storage(size_t memorySize, size_t blockSize) {
    this->memorySize = memorySize;
    this->blockSize = blockSize;
    this->blocks = operator new(memorySize);
}
