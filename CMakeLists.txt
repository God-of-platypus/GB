cmake_minimun_required(VERSION 3.28)

project(GB C)

target_compile_options(GB PRIVATE -Wall -Wextra -pedantic -Werror)

target_include_directories(GB PUBLIC "include/")

add_subdirectory(src)

add_subdirectory(testsuite)
