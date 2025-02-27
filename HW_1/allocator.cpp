//
// Created by Sergei on 10/28/24.
//

#include "allocator.h"
#include <iostream>

Allocator::Allocator() : memory(nullptr), totalSize(0), offset(0) {}

void Allocator::makeAllocator(size_t maxSize) {
    if(memory != nullptr){
        delete[] memory;
        memory = nullptr;
    }

    totalSize = maxSize;
    memory = new char[maxSize];
    offset = 0;
}

char *Allocator::alloc(size_t size) {
    if(offset + size > totalSize){
        return nullptr;
    }

    char *block = memory + offset;
    offset += size;
    return block;
}

void Allocator::reset() {
    offset = 0;
}

Allocator::~Allocator(){
    delete[] memory;
};