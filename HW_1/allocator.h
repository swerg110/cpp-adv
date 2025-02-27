//
// Created by Sergei on 10/28/24.
//

#ifndef HW_1_ALLOCATOR_H
#define HW_1_ALLOCATOR_H

#include <cstdio>

class Allocator {
private:

    char *memory;
    size_t totalSize;
    size_t offset;
public:
    Allocator();

    void makeAllocator(size_t maxSize);

    char *alloc(size_t size);

    void reset();

    ~Allocator();
};


#endif //HW_1_ALLOCATOR_H
