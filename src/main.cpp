#include <iostream>
#include <fstream>

#include "version.h"
#include "cxxopts.hpp"
#include "hexdecoder.h"
#include "termcolor/termcolor.hpp"

int main(int argc, char* argv[])
{

    cxxopts::Options options("ihexcrccheck", "Validates Intel HEX checksums, with error output.");

    /* Add options */
    options.add_options()
    ("f,file", "File name", cxxopts::value<std::string>())
    ("h,help", "Shows this help");

    try
    {
        auto parsedArgs = options.parse(argc, argv);
        if ((parsedArgs.count("help") == 1 && parsedArgs["help"].as<bool>()) || (parsedArgs.count("file") != 1))
        {
            std::cout << options.help() << std::endl;
        }
        else
        {
            std::string filepath = parsedArgs["file"].as<std::string>();
            std::fstream fileStream;
            std::string line;
            fileStream.open(filepath, std::ios_base::in);
            if (fileStream.is_open())
            {
                std::cout << "Decoding Hex, v" << APP_VERSION_STRING << " " << filepath << std::endl;

                while (!fileStream.eof() && !fileStream.fail())
                {
                    std::getline(fileStream, line);
                    
                    if (!HexDecoder::isValid(line))
                    {
                        std::cout << termcolor::blue << line << termcolor::reset << std::endl;
                    }
                }

                fileStream.close();
            }
            else
            {
                std::cout << "Error opening file " << filepath << std::endl;
            }
            
        }
    }
    catch(const cxxopts::OptionParseException& e)
    {
        std::cout << e.what() << std::endl;
        std::cout << options.help() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    
    return 0;
}