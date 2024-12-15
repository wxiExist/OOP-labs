cmake_minimum_required(VERSION 3.10)

project(laba5)

add_executable(GCDTest unit.cpp)
target_link_libraries(GCDTest gtest gtest_main)
target_compile_features(GCDTest PRIVATE cxx_std_17) 
