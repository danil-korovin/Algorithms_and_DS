#include "ascii85.h"
#include <gtest/gtest.h>
#include <sstream>
#include <iostream>

// Передаём ссылку на строку для кодировки
std::string encodeString(const std::string& input) {
    std::vector<std::uint8_t> data(input.begin(), input.end());
    return ascii85_encode(data);
}

// Передаём ссылку на строку для раскодировки
std::string decodeString(const std::string& input) {
    std::vector<std::uint8_t> decoded = ascii85_decode(input);
    return std::string(decoded.begin(), decoded.end());
}

TEST(Test1, EncodeEmptyString) {
    ASSERT_EQ(encodeString(""), "");
}

TEST(Test2, DecodeEmptyString) {
    ASSERT_EQ(decodeString(""), "");
}


TEST(Test3, EncodeString) {
    ASSERT_EQ(encodeString("Hello, World!"), "87cURD_*#4DfTZ)+TMKB");
}


TEST(Test4, Decode_zeros) {
    ASSERT_EQ(decodeString("z"), "\0\0\0\0");
}

