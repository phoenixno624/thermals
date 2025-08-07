cmake_minimum_required(VERSION 3.10)

project(thermals)

include_directories(inc)
add_executable(thermals src/main.c src/thermals.c inc/thermals.h)