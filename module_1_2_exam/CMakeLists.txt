cmake_minimum_required(VERSION 3.14)
project(OwnStdlibTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(own_stdlib_tests
  src/hardware_register/own_stdlib.cpp
  src/hardware_register/hardware_register.cpp
  src/event_system/function_pointers.cpp
  src/static_pool.cpp
  tests/test_own_stdlib.cpp
  tests/test_hardware_register.cpp
  tests/test_events.cpp
  tests/test_static_pool.cpp
)

target_include_directories(own_stdlib_tests PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/src/hardware_register
  ${CMAKE_CURRENT_SOURCE_DIR}/src/event_system
)
target_link_libraries(own_stdlib_tests PRIVATE GTest::gtest_main)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_link_options(own_stdlib_tests PRIVATE "-static-libgcc" "-static-libstdc++")
endif()

enable_testing()
include(GoogleTest)
gtest_discover_tests(own_stdlib_tests)
