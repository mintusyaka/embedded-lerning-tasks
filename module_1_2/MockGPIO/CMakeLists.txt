cmake_minimum_required(VERSION 3.14)
project(MockGPIO LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(MockGPIOTest
    mock_gpio.cpp
    test.cpp
)

target_include_directories(MockGPIOTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(MockGPIOTest PRIVATE gtest_main)

# On MinGW/GNU builds the produced exe may depend on libstdc++/libgcc DLLs
# which may not be found at runtime. Statically link those to produce a
# standalone executable when using GNU toolchain.
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_link_options(MockGPIOTest PRIVATE "-static-libgcc" "-static-libstdc++")
endif()

enable_testing()
add_test(NAME MockGPIOTest COMMAND MockGPIOTest)
