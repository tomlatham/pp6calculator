# - Main CMake script for pp6calculator
# Comments in CMake begin with a '#' just like shell and python scripts
#
# - Require latest generation of CMake
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# - Declare the project
project(pp6calculator)

# - Use standard flag set when using the GNU compiler
if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "-std=c++98 -pedantic-errors -Wall -Wextra -Werror -Wfatal-errors -Wwrite-strings -Woverloaded-virtual -fno-nonansi-builtins -fno-gnu-keywords -fstrict-aliasing")
endif()

# - Tell compiler where to find headers
include_directories(FileReader)
include_directories(PP6Lib)

# - Add the PP6Lib and FileReader libraries
add_subdirectory(PP6Lib)
add_subdirectory(FileReader)

# - Add the pp6calculator program
add_executable(pp6calculator pp6calculator.cpp)

# - Link pp6calculator to pp6lib and FileReader library
target_link_libraries(pp6calculator pp6lib FileReader)

# - Install pp6calculator to the bin subdirectory of CMAKE_INSTALL_PREFIX
install(TARGETS pp6calculator DESTINATION bin)

# - Copy PDG text DB to build directory so it's immediately available
configure_file(pdg.dbt ${PROJECT_BINARY_DIR}/pdg.dbt COPYONLY)

# - Package pp6calculator sources and executable
include(CPack)

