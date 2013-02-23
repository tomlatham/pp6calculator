# - Main CMake script for pp6calculator
# Comments in CMake begin with a '#' just like shell and python scripts
#
# - Require latest generation of CMake
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# - Declare the project
project(pp6calculator)

# - Tell compiler where to find headers
include_directories(PP6Lib)

# - Add the pp6calculator program
add_executable(pp6calculator pp6calculator.cpp PP6Lib/PP6Math.cpp 
  PP6Lib/PP6Math.hpp)

