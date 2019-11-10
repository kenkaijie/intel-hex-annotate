cmake_minimum_required(VERSION 3.1...3.15)

project(ihexcrccheck VERSION 0.1.0
                     DESCRIPTION "Validates intel hex files" 
                     LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

configure_file(src/version.h.in version.h)

add_executable(${PROJECT_NAME} src/main.cpp)

add_subdirectory(extern/cxxopts)
target_link_libraries(${PROJECT_NAME} PRIVATE cxxopts)

add_subdirectory(lib/hexdecoder)
target_link_libraries(${PROJECT_NAME} PRIVATE hexdecoder)

add_subdirectory(extern/termcolor)
target_link_libraries(${PROJECT_NAME} PRIVATE termcolor)

target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_BINARY_DIR}")

add_subdirectory(extern/googletest)
enable_testing()
