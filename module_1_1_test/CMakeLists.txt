cmake_minimum_required(VERSION 3.15)
project(module1_1_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${CMAKE_SOURCE_DIR}/src/include)

file(GLOB_RECURSE MODULE_SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

list(REMOVE_ITEM MODULE_SOURCES
    ${CMAKE_SOURCE_DIR}/src/volatile_test.cpp
    ${CMAKE_SOURCE_DIR}/src/const_constexpr.cpp
)

add_executable(test_all
    test_all.cpp
    ${MODULE_SOURCES}
)
