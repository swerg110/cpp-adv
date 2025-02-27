//
// Created by Sergei on 12/5/24.
//
#include "tokenParser.cpp"
#include <gtest/gtest.h>

TEST(TokenParserTest, ParseNumbersAndStrings) {
    TokenParser parser;

    bool startCalled = false;
    bool endCalled = false;
    std::vector<uint64_t> numbers;
    std::vector<std::string> strings;

    parser.setStartCallback([&]() { startCalled = true; });
    parser.setEndCallback([&]() { endCalled = true; });
    parser.setDigitTokenCallback([&](uint64_t num) { numbers.push_back(num); });
    parser.setStringTokenCallback([&](const std::string &str) { strings.push_back(str); });

    std::string input = "hello 123 world 456";
    parser.parse(input);

    ASSERT_TRUE(startCalled);
    ASSERT_TRUE(endCalled);
    ASSERT_EQ(numbers, std::vector<uint64_t>({123, 456}));
    ASSERT_EQ(strings, std::vector<std::string>({"hello", "world"}));
}

TEST(TokenParserTest, HandleEmptyString) {
    TokenParser parser;

    bool startCalled = false;
    bool endCalled = false;

    parser.setStartCallback([&]() { startCalled = true; });
    parser.setEndCallback([&]() { endCalled = true; });

    parser.parse("");

    ASSERT_TRUE(startCalled);
    ASSERT_TRUE(endCalled);
}

TEST(TokenParserTest, HandleStringToken) {
    TokenParser parser;

    bool stringHandled = false;
    parser.setStringTokenCallback([&](const std::string &str) { stringHandled = true; });

    parser.parse("hello");
    ASSERT_TRUE(stringHandled);
}

TEST(TokenParserTest, HandleLargeNumbersAsStrings) {
    TokenParser parser;

    std::vector<std::string> strings;
    parser.setStringTokenCallback([&](const std::string &str) { strings.push_back(str); });

    parser.parse("18446744073709551616");
    ASSERT_EQ(strings, std::vector<std::string>({"18446744073709551616"}));
}

TEST(TokenParserTest, HandleMixedTokens) {
    TokenParser parser;

    std::vector<uint64_t> numbers;
    std::vector<std::string> strings;

    parser.setDigitTokenCallback([&](uint64_t num) { numbers.push_back(num); });
    parser.setStringTokenCallback([&](const std::string &str) { strings.push_back(str); });

    parser.parse("42 foo bar 9999");
    ASSERT_EQ(numbers, std::vector<uint64_t>({42, 9999}));
    ASSERT_EQ(strings, std::vector<std::string>({"foo", "bar"}));
}

TEST(TokenParserTest, NoCallbacksSet) {
    TokenParser parser;

    parser.parse("123 abc");
    SUCCEED();
}

TEST(TokenParserTest, HandleLeadingZeros) {
    TokenParser parser;

    std::vector<uint64_t> numbers;

    parser.setDigitTokenCallback([&](uint64_t num) { numbers.push_back(num); });

    parser.parse("00001 002 03");
    ASSERT_EQ(numbers, std::vector<uint64_t>({1, 2, 3}));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}