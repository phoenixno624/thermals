cmake_minimum_required(VERSION 3.10)

project(thermals)

include_directories(inc)
add_executable(
    thermals
    src/main.cpp
    src/thermals.cpp
    inc/thermals.hpp)

target_compile_features(thermals PRIVATE cxx_std_20)