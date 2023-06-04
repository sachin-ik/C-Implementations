#cmake to build main.c
cmake_minimum_required(VERSION 3.0)

project(main)

#GLOB all .c files in the current directory and store in SRC
file(GLOB SRC *.c)

add_executable(main ${SRC})
