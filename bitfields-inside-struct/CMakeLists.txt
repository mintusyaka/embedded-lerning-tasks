cmake_minimum_required(VERSION 3.16)
project(bitfield_struct LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(bitfield_test
    test-bit-field-size.cpp
    bit-field-struct.hpp
    bit-field-union.hpp
)

target_link_libraries(bitfield_test PRIVATE gtest_main)

target_include_directories(bitfield_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

enable_testing()
add_test(NAME bitfield_test COMMAND bitfield_test)
