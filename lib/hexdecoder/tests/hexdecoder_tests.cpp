#include <gtest/gtest.h>
#include <string>
#include<hexdecoder.h>

TEST(hexdecoder_tests, test_valid_hex_line) {
    std::string hexStr = ":103FF000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD1";

    bool actual = HexDecoder::isValid(hexStr);
    ASSERT_TRUE(actual == true);
}

TEST(hexdecoder_tests, test_invalid_hex_line) {
    std::string hexStr = ":103FF000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD1";

    bool actual = HexDecoder::isValid(hexStr);
    ASSERT_TRUE(actual == false);
}