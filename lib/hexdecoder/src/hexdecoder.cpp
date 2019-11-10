#include "hexdecoder.h"
#include <regex>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <iostream>

bool HexDecoder::isValid(std::string const& hexString)
{
    // given the string, we do the following checks
    // - Length check
    // - Format check
    // - Checksum check

    bool isValid = true;

    std::regex emptyChecker("^[\\n\\r\\s]*$", std::regex::extended);
    if (std::regex_match(hexString, emptyChecker, std::regex_constants::match_any))
    {
        return true;
    }

    // format check
    std::regex formatChecker("^:[0-9a-fA-F]+?$");

    isValid &= std::regex_match(hexString, formatChecker, std::regex_constants::match_any);
    if (!isValid)
    {
        std::cout << "Invalid Regex" << std::endl;
        return isValid;
    }

    // length check
    std::string byteData = hexString.substr(1);

    isValid &= (byteData.length() % 2 == 0);
    if (!isValid)
    {
        std::cout << "Invalid String Length" << std::endl;
        return isValid;
    }

    std::vector<uint8_t> bytes;

    for (std::size_t idx = 0; idx < byteData.length(); idx+=2)
    {
        char* end; // ignore this, we just discard it
        std::string hexString = byteData.substr(idx, 2);
        uint8_t byte = static_cast<uint8_t>(std::strtoul(hexString.c_str(), &end, 16) & 0xFF);
        bytes.push_back(byte);
    }

    isValid &= (bytes[0]*2 + MIN_HEX_STRING_SIZE) == byteData.length();
    isValid &= (bytes.size() == bytes[0] + MIN_HEX_STRING_SIZE/2);
    if (!isValid)
    {
        std::cout << "Invalid Length" << std::endl;
        return isValid;
    }


    // checksum check
    auto sum = std::accumulate(bytes.rbegin(), bytes.rend(), 0UL);
    isValid &= (sum & 0xFF) == 0;

    if (!isValid)
    {
        std::cout << "Invalid checksum" << std::endl;
    }

    return isValid;
}