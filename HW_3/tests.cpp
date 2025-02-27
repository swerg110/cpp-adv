//
// Created by Sergei on 11/29/24.
//
#include "matrix.h"
#include <gtest/gtest.h>


TEST(MatrixTests, CopyConstructorTest) {
    Matrix m1(2, 2);
    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][0] = 3; m1[1][1] = 4;

    Matrix m2 = m1;

    EXPECT_EQ(m2.getRows(), 2);
    EXPECT_EQ(m2.getColumns(), 2);

    EXPECT_EQ(m2[0][0], 1);
    EXPECT_EQ(m2[0][1], 2);
    EXPECT_EQ(m2[1][0], 3);
    EXPECT_EQ(m2[1][1], 4);

    m2[0][0] = 10;
    EXPECT_EQ(m1[0][0], 1);
    EXPECT_EQ(m2[0][0], 10);
}
TEST(MatrixTests, ConstructorTest) {
    Matrix m(3, 4);
    EXPECT_EQ(m.getRows(), 3);
    EXPECT_EQ(m.getColumns(), 4);
}

TEST(MatrixTests, AccessOperatorTest) {
    Matrix m(2, 2);
    m[0][0] = 1;
    m[0][1] = 2;
    m[1][0] = 3;
    m[1][1] = 4;

    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[0][1], 2);
    EXPECT_EQ(m[1][0], 3);
    EXPECT_EQ(m[1][1], 4);
}

TEST(MatrixTests, OutOfRangeTest) {
    Matrix m(2, 2);
    EXPECT_THROW(m[2][0] = 1, std::out_of_range);
    EXPECT_THROW(m[0][2] = 1, std::out_of_range);
}

TEST(MatrixTests, AssignmentOperatorTest) {
    Matrix m1(2, 2);
    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][0] = 3; m1[1][1] = 4;

    Matrix m2(2, 2);
    m2 = m1;

    EXPECT_EQ(m2.getRows(), 2);
    EXPECT_EQ(m2.getColumns(), 2);

    EXPECT_EQ(m2[0][0], 1);
    EXPECT_EQ(m2[0][1], 2);
    EXPECT_EQ(m2[1][0], 3);
    EXPECT_EQ(m2[1][1], 4);

    m2[1][1] = 10;
    EXPECT_EQ(m1[1][1], 4);
    EXPECT_EQ(m2[1][1], 10);
}

TEST(MatrixTests, AssignmentToSelfTest) {
    Matrix m(2, 2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;

    m = m;

    EXPECT_EQ(m.getRows(), 2);
    EXPECT_EQ(m.getColumns(), 2);

    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[0][1], 2);
    EXPECT_EQ(m[1][0], 3);
    EXPECT_EQ(m[1][1], 4);
}

TEST(MatrixTests, MultiplyByNumberTest) {
    Matrix m(2, 2);
    m[0][0] = 1;
    m[0][1] = 2;
    m[1][0] = 3;
    m[1][1] = 4;

    m *= 2;

    EXPECT_EQ(m[0][0], 2);
    EXPECT_EQ(m[0][1], 4);
    EXPECT_EQ(m[1][0], 6);
    EXPECT_EQ(m[1][1], 8);
}

TEST(MatrixTests, AddMatricesTest) {
    Matrix m1(2, 2);
    Matrix m2(2, 2);

    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][0] = 3; m1[1][1] = 4;

    m2[0][0] = 5; m2[0][1] = 6;
    m2[1][0] = 7; m2[1][1] = 8;

    Matrix m3 = m1 + m2;

    EXPECT_EQ(m3[0][0], 6);
    EXPECT_EQ(m3[0][1], 8);
    EXPECT_EQ(m3[1][0], 10);
    EXPECT_EQ(m3[1][1], 12);
}

TEST(MatrixTests, CompareMatricesTest) {
    Matrix m1(2, 2);
    Matrix m2(2, 2);

    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][0] = 3; m1[1][1] = 4;

    m2[0][0] = 1; m2[0][1] = 2;
    m2[1][0] = 3; m2[1][1] = 4;

    EXPECT_TRUE(m1 == m2);

    m2[1][1] = 5;
    EXPECT_FALSE(m1 == m2);
    EXPECT_TRUE(m1 != m2);
}

TEST(MatrixTests, StreamOutputTest) {
    Matrix m(2, 2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;

    std::ostringstream oss;
    oss << m;

    std::string expected_output = "1\t2\n3\t4\n";
    EXPECT_EQ(oss.str(), expected_output);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
