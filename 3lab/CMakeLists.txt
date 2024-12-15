cmake_minimum_required(VERSION 3.10)

project(FigureInheritance LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(FigureInheritance main.cpp)

if (MSVC)
    target_compile_options(FigureInheritance PRIVATE /W4 /WX)
else()
    target_compile_options(FigureInheritance PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

enable_testing()
