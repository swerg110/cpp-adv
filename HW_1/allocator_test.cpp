//
// Created by Sergei on 12/5/24.
//
#include "allocator.h"
#include <gtest/gtest.h>

TEST(AllocatorTest, AllocatesMemoryWithinMaxSize) {
    Allocator allocator;
    allocator.makeAllocator(100);

    char *ptr1 = allocator.alloc(10);
    ASSERT_NE(ptr1, nullptr);

    char *ptr2 = allocator.alloc(20);
    ASSERT_NE(ptr2, nullptr);
    ASSERT_NE(ptr1, ptr2);

    char *ptr3 = allocator.alloc(80);
    ASSERT_EQ(ptr3, nullptr);
}

TEST(AllocatorTest, ResetAllowsReuseOfMemory) {
    Allocator allocator;
    allocator.makeAllocator(50);

    char *ptr1 = allocator.alloc(25);
    ASSERT_NE(ptr1, nullptr);

    allocator.reset();

    char *ptr2 = allocator.alloc(25);
    ASSERT_NE(ptr2, nullptr);
    ASSERT_EQ(ptr1, ptr2);
}

TEST(AllocatorTest, MakeAllocatorReallocatesMemory) {
    Allocator allocator;
    allocator.makeAllocator(30);

    char *ptr1 = allocator.alloc(20);
    ASSERT_NE(ptr1, nullptr);

    allocator.makeAllocator(50);

    char *ptr2 = allocator.alloc(40);
    ASSERT_NE(ptr2, nullptr);
    ASSERT_NE(ptr1, ptr2);
}

TEST(AllocatorTest, AllocatorHandlesMultipleAllocationsWithoutLeak) {
    Allocator allocator;
    allocator.makeAllocator(100);
    for (int i = 0; i < 10; ++i) {
    char *ptr = allocator.alloc(10);
    ASSERT_NE(ptr, nullptr);
}
}

TEST(AllocatorTest, AllocZeroSizeReturnsNonNullPointer) {
    Allocator allocator;
    allocator.makeAllocator(10);

    char *ptr = allocator.alloc(0);
    ASSERT_NE(ptr, nullptr);
}

TEST(AllocatorTest, AllocWithoutInitializationReturnsNull) {
    Allocator allocator;

    char *ptr = allocator.alloc(10);
    ASSERT_EQ(ptr, nullptr);
}
TEST(AllocatorTest, AllocExactMaxSize) {
    Allocator allocator;
    allocator.makeAllocator(50);

    char *ptr = allocator.alloc(50);
    ASSERT_NE(ptr, nullptr);

    char *ptr2 = allocator.alloc(1);
    ASSERT_EQ(ptr2, nullptr);
}

TEST(AllocatorTest, AllocAfterResetWorksCorrectly) {
    Allocator allocator;
    allocator.makeAllocator(50);

    allocator.alloc(20);
    allocator.reset();

    char *ptr = allocator.alloc(50);
    ASSERT_NE(ptr, nullptr);
}
TEST(AllocatorTest, ResetDoesNotDeallocateMemory) {
    Allocator allocator;
    allocator.makeAllocator(30);

    char *ptr1 = allocator.alloc(15);
    ASSERT_NE(ptr1, nullptr);

    allocator.reset();

    char *ptr2 = allocator.alloc(15);
    ASSERT_EQ(ptr2, ptr1);
}

TEST(AllocatorTest, AllocTooLargeBlockReturnsNull) {
    Allocator allocator;
    allocator.makeAllocator(30);

    char *ptr = allocator.alloc(31);
    ASSERT_EQ(ptr, nullptr);
}