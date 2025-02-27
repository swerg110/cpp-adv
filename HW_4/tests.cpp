//
// Created by Sergei on 1/9/25.
//
#include <gtest/gtest.h>

#include "biginteger.h"
#include <iostream>
#include <sstream>

TEST(bigintTests, ConstructorFromString) {
    bigint b1("1234567890");
    std::ostringstream oss;
    oss << b1;
    EXPECT_EQ(oss.str(), "1234567890");
}

TEST(bigintTests, AddbigintAndInt) {
    bigint b1("1234567890");
    bigint result = b1 + 123;
    std::ostringstream oss;
    oss << result;
    EXPECT_EQ(oss.str(), "1234568013");
}

TEST(bigintTests, Addbigint) {
    bigint b1("1234567890");
    bigint b2("9876543210");
    bigint result = b1 + b2;
    std::ostringstream oss;
    oss << result;
    EXPECT_EQ(oss.str(), "11111111100");
}

TEST(bigintTests, MultiplybigintAndInt) {
    bigint b1("1234567890");
    bigint result = b1 * 2;
    std::ostringstream oss;
    oss << result;
    EXPECT_EQ(oss.str(), "2469135780");
}

TEST(bigintTests, Multiplybigint) {
    bigint b1("1234567890");
    bigint b2("9876543210");
    bigint result = b1 * b2;
    std::ostringstream oss;
    oss << result;
    EXPECT_EQ(oss.str(), "1219326311126352690");
}
TEST(bigintTests, UnaryMinusTest) {
    bigint b1("1234567890");
    bigint b2("-1234567890");
    
    bigint result1 = -b1;
    std::ostringstream oss1;
    oss1 << result1;
    EXPECT_EQ(oss1.str(), "-1234567890");
    
    bigint result2 = -b2;
    std::ostringstream oss2;
    oss2 << result2;
    EXPECT_EQ(oss2.str(), "1234567890");
}

TEST(bigintTests, NegativeNumberTest) {
    bigint b1("-1234567890");
    std::ostringstream oss;
    oss << b1;
    EXPECT_EQ(oss.str(), "-1234567890");
    
    bigint b2("-9876543210");
    std::ostringstream oss2;
    oss2 << b2;
    EXPECT_EQ(oss2.str(), "-9876543210");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}