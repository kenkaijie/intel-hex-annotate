add_library(hexdecoder STATIC src/hexdecoder.cpp include/hexdecoder.h)
target_include_directories(hexdecoder PUBLIC include)

# Tests

add_executable(hexdecoder_test tests/hexdecoder_tests.cpp)
target_link_libraries(hexdecoder_test PUBLIC hexdecoder gtest_main)
add_test(NAME hexdecoder_test COMMAND hexdecoder_test)