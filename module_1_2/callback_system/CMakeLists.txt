cmake_minimum_required(VERSION 3.14)
project(CallbackSystemTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(test_timer_driver
  tests/test_timer_driver.cpp
  modules/timer_driver.cpp
)

target_include_directories(test_timer_driver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/modules)
target_link_libraries(test_timer_driver PRIVATE GTest::gtest_main)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_link_options(test_timer_driver PRIVATE "-static-libgcc" "-static-libstdc++")
endif()

include(GoogleTest)
gtest_discover_tests(test_timer_driver)