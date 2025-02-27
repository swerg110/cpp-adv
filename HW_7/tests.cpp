#include <gtest/gtest.h>
#include "avl.h"

TEST(AVLArrayTest, InsertAndFind) {
avl_array<int, int, size_t, 10> tree;

EXPECT_TRUE(tree.insert(10, 100));
EXPECT_TRUE(tree.insert(20, 200));
EXPECT_TRUE(tree.insert(5, 50));

auto it = tree.find(10);
EXPECT_NE(it, tree.end());
EXPECT_EQ(*it, 100);

it = tree.find(20);
EXPECT_NE(it, tree.end());
EXPECT_EQ(*it, 200);

it = tree.find(5);
EXPECT_NE(it, tree.end());
EXPECT_EQ(*it, 50);

EXPECT_EQ(tree.find(15), tree.end());
}

TEST(AVLArrayTest, UpdateValues) {
avl_array<int, int, size_t, 10> tree;

EXPECT_TRUE(tree.insert(10, 100));
EXPECT_TRUE(tree.insert(10, 200));

auto it = tree.find(10);
EXPECT_NE(it, tree.end());
EXPECT_EQ(*it, 200);
}

TEST(AVLArrayTest, OperatorAccess) {
avl_array<int, int, size_t, 10> tree;

tree[10] = 100;
tree[20] = 200;

EXPECT_EQ(tree[10], 100);
EXPECT_EQ(tree[20], 200);

EXPECT_EQ(tree[30], 0);
tree[30] = 300;
EXPECT_EQ(tree[30], 300);
}

TEST(AVLArrayTest, SizeAndEmpty) {
    avl_array<int, int, size_t, 10> tree;

    EXPECT_TRUE(tree.empty());
    EXPECT_EQ(tree.size(), 0);

    tree.insert(10, 100);
    tree.insert(20, 200);
    tree.insert(5, 50);

    EXPECT_FALSE(tree.empty());
    EXPECT_EQ(tree.size(), 3);

    tree.clear();
    EXPECT_TRUE(tree.empty());
    EXPECT_EQ(tree.size(), 0);
}

TEST(AVLArrayTest, Capacity) {
    avl_array<int, int, size_t, 3> tree;

    EXPECT_TRUE(tree.insert(10, 100));
    EXPECT_TRUE(tree.insert(20, 200));
    EXPECT_TRUE(tree.insert(30, 300));

    EXPECT_FALSE(tree.insert(40, 400));

    EXPECT_EQ(tree.size(), 3);
    EXPECT_NE(tree.find(10), tree.end());
    EXPECT_NE(tree.find(20), tree.end());
    EXPECT_NE(tree.find(30), tree.end());
    EXPECT_EQ(tree.find(40), tree.end());
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
