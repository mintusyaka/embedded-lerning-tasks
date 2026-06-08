cmake_minimum_required(VERSION 3.10)
project(bit_operations_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(test-bits-operations test-bits-operations.cpp)

enable_testing()
add_test(NAME bit_operations COMMAND test-bits-operations)
