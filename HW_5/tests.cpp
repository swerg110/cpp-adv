//
// Created by Sergei on 11/29/24.
//
#include <gtest/gtest.h>
#include "Serializer.h"
#include "Deserializer.h"
#include "Data.h"

TEST(SerializerTest, Serialization) {
    Data x{1, true, 2};
    std::stringstream stream;

    Serializer serializer(stream);
    Error err = serializer.save(x);

    ASSERT_EQ(err, Error::NoError);
    ASSERT_EQ(stream.str(), "1 true 2 ");
}

TEST(DeserializerTest, Deserialization) {
    Data y{0, false, 0};
    std::stringstream stream("1 true 2");

    Deserializer deserializer(stream);
    Error err = deserializer.load(y);

    ASSERT_EQ(err, Error::NoError);
    ASSERT_EQ(y.a, 1);
    ASSERT_EQ(y.b, true);
    ASSERT_EQ(y.c, 2);
}

TEST(DeserializerTest, CorruptedData){
    Data y{0, false, 0};
    std::stringstream stream("1 invalid 2");

    Deserializer deserializer(stream);
    Error err = deserializer.load(y);

    ASSERT_EQ(err, Error::CorruptedArchive);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
