cmake_minimum_required(VERSION 3.20)

project(Lab2)

add_executable(lab2 main.cpp include/lab2.h src/lab2.cpp)

target_include_directories(lab2 PRIVATE include)
