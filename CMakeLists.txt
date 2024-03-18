cmake_minimum_required(VERSION 3.28)

project(GB C)

add_executable(GB)

target_compile_options(GB PRIVATE -Wall -Wextra -pedantic -Werror -g)

target_include_directories(GB PUBLIC "include/")

find_library(SDL2 PRIVATE SDL2 sdl2 REQUIRED)

target_link_libraries(GB PRIVATE ${SDL2})

add_subdirectory(src)

add_subdirectory(testsuite)
