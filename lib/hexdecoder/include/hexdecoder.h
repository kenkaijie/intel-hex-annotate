#pragma once

#include <string>
#include <stdint.h>
#include <vector>

// Class for decoding a hex file.
class HexDecoder
{
    public:
        static constexpr uint8_t MIN_HEX_STRING_SIZE = 10;

        static bool isValid(std::string const& hexRowString);

};

