cmake_minimum_required(VERSION 3.7)
project(Tree_AVL)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c arvore.c)
add_executable(Tree_AVL ${SOURCE_FILES})