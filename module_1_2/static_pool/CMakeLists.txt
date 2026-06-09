cmake_minimum_required(VERSION 3.14)
project(StaticPoolTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(static_pool_tests
  static_pool.cpp
  test_static_pool.cpp
)

target_include_directories(static_pool_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(static_pool_tests PRIVATE gtest_main)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_link_options(static_pool_tests PRIVATE "-static-libgcc" "-static-libstdc++")
endif()

enable_testing()
add_test(NAME static_pool_tests COMMAND static_pool_tests)
