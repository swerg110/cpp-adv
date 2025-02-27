//
// Created by Sergei on 12/24/24.
//
#include <gtest/gtest.h>
#include "format.h"

TEST(FormatTests, BasicFormatting) {
    EXPECT_EQ(format("Hello, {0}!", "World"), "Hello, World!");
    EXPECT_EQ(format("Sum: {0} + {1} = {2}", 2, 3, 5), "Sum: 2 + 3 = 5");
    EXPECT_EQ(format("Values: {0}, {1}, {2}", 1, 2, 3), "Values: 1, 2, 3");
}

TEST(FormatTests, NestedBracesThrowsException) {
    EXPECT_THROW(format("Nested {{0}}", "value"), FormatException);
}

TEST(FormatTests, UnmatchedClosingBraceThrowsException) {
    EXPECT_THROW(format("Unmatched brace: }"), FormatException);
}

TEST(FormatTests, ArgumentIndexExceedsThrowsException) {
    EXPECT_THROW(format("Out of range: {1}", "only_one_arg"), FormatException);
}

TEST(FormatTests, InvalidCharacterInBracesThrowsException) {
    EXPECT_THROW(format("Invalid character: {a}"), FormatException);
}

TEST(FormatTests, MissingClosingBraceThrowsException) {
    EXPECT_THROW(format("Missing closing brace: {0", "arg"), FormatException);
}

TEST(FormatTests, UnusedArgumentsThrowsException) {
    EXPECT_THROW(format("Unused argument example: {0}", "arg1", "unused_arg"), FormatException);
}

TEST(FormatTests, EmptyString) {
    EXPECT_EQ(format(""), "");
}

TEST(FormatTests, NoArguments) {
    EXPECT_EQ(format("Static string with no placeholders"), "Static string with no placeholders");
}

TEST(FormatTests, MultitypeArguments) {
    EXPECT_EQ(format("Mixed types: {0}, {1}, {2}", 123, 45.67, "text"), "Mixed types: 123, 45.67, text");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
