cmake_minimum_required(VERSION 3.22)
project(linked_list C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(linked_list
        linked_list.c
        linked_list.h
        main.c)
