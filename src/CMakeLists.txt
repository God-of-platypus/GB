cmake_minimum_required(VERSION 3.28)

target_sources(GB PUBLIC main.c)

add_subdirectory(gameboy)

add_subdirectory(register)

add_subdirectory(instruction)
