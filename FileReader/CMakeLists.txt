# - Top level CMake script for FileReader library
#
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(FileReader)

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "-std=c++98 -pedantic-errors -Wall -Wextra -Werror -Wfatal-errors -Wwrite-strings -Woverloaded-virtual -fno-nonansi-builtins -fno-gnu-keywords -fstrict-aliasing")
endif()

add_library(FileReader FileReader.hpp FileReader.cpp)
