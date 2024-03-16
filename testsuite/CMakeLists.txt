cmake_minimum_required(VERSION 3.28)                                             
                                                                                 
project(criterion)                                                            
                                                                                 
find_library(CRITERION NAMES criterion lcriterion REQUIRED)

add_executable(test test.c 
    ../src/gameboy/gameboy.c
    ../src/register/register.c)                                            

target_include_directories(test PUBLIC "../include/")
target_link_libraries(test PRIVATE ${CRITERION})    
