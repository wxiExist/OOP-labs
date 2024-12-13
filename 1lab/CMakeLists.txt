cmake_minimum_required(VERSION 3.10)

project(MyProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(main main.cpp gcd.cpp)

add_executable(test_gcd test_gcd.cpp gcd.cpp)

include_directories(${CMAKE_SOURCE_DIR}/gtest/include)

target_link_libraries(test_gcd ${CMAKE_SOURCE_DIR}/gtest/lib/libgtest.a ${CMAKE_SOURCE_DIR}/gtest/lib/libgtest_main.a)

enable_testing()
add_test(NAME GCDTest COMMAND test_gcd)
