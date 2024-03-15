cmake_minimum_required(VERSION 3.28)

project(test)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(test
    ./test.c
    )

target_link_libraries(test GTest::gtest GTest::gtest_main)

