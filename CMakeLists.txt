#CMake file to build c files

cmake_minimum_required(VERSION 3.0)

project(C_Implementations)

add_executable(linkedlist linkedList.c)
add_executable(softwareTimer softwareTimer.c)
add_executable(bitMan bitManipulations.c)



