FileReader - A simple C++ based line reader for text files
==========================================================
This is the README for the FileReader project, a simple text file line 
reader written in C++ for use in the MPAGS PP6 course on software 
development with C++.

Authors
-------
- Andrew Bennieston
- Tom Latham
- Ben Morgan
- Mark Slater

License
-------
FileReader is distributed under the terms of the Boost Software License.

News
----
This is the release version for Day 2 of the PP6 Course.

Installation
============
Prerequisites
-------------
- Unix operating system (Windows OS should work, but is not tested)
- C++98/11 compiler (`g++`/`clang++` tested)
- [CMake](http://www.cmake.org) build tool, version 2.8 or higher

Building FileReader
-------------------
If you are dropping FileReader into an existing CMake based project, simply
add this directory to the build of your project using CMake's 
`add_subdirectory` command. You can also just add the `FileReader.hpp`
and `FileReader.cpp` files to your application or library.

If you are building FileReader as a standalone library, then we recommend
the following sequence of steps to build the `FileReader` library using
CMake and UNIX Makefiles:

1. Create a build directory parallel to the directory holding this README,
e.g.

        $ ls
        FileReader-1.0.0
        $ mkdir FileReader-1.0.0.build

2. Change into the build directory and run `cmake`, pointing it to the 
source directory (i.e., the directory holding this README:

        $ cd FileReader-1.0.0.build
        $ cmake ../FileReader-1.0.0
        -- The C compiler identification is GNU 4.2.1
        -- The CXX compiler identification is GNU 4.2.1
        -- Checking whether C compiler has -isysroot
        -- Checking whether C compiler has -isysroot - yes
        -- Checking whether C compiler supports OSX deployment target flag
        -- Checking whether C compiler supports OSX deployment target flag - yes
        -- Check for working C compiler: /usr/bin/cc
        -- Check for working C compiler: /usr/bin/cc -- works
        -- Detecting C compiler ABI info
        -- Detecting C compiler ABI info - done
        -- Checking whether CXX compiler has -isysroot
        -- Checking whether CXX compiler has -isysroot - yes
        -- Checking whether CXX compiler supports OSX deployment target flag
        -- Checking whether CXX compiler supports OSX deployment target flag - yes
        -- Check for working CXX compiler: /usr/bin/c++
        -- Check for working CXX compiler: /usr/bin/c++ -- works
        -- Detecting CXX compiler ABI info
        -- Detecting CXX compiler ABI info - done
        -- Configuring done
        -- Generating done
        -- Build files have been written to: /Users/FileReader/FileReader-1.0.0.build
        $

    The above output is for Mac OS X 10.6.8, so will vary slightly on other 
    systems. However, you should see the last three lines, which indicate
    a successful configuration.

3. Run `make` using the freshly generated Makefile:

        $ make
        Scanning dependencies of target FileReader
        [100%] Building CXX object CMakeFiles/FileReader.dir/FileReader.cpp.o
        Linking CXX static library libFileReader.a
        [100%] Built target FileReader
       
    The build should complete without warning or error.

At present, FileReader does not provide an installation method.    

Using FileReader in your Application
====================================
The FileReader library can be used as follows in C++ code:

```
#include "FileReader.hpp"
...
// Open the file to be read
FileReader f("filename.txt");

// Only process if the file is open/valid
if (f.isValid()) {
  // Loop until out of lines
  while (f.nextLine()) {
    // Fields in each line line are treated as whitespace separated
    // and counted from 1. Fields can be retrieved as one of four main
    // types

    // retrieve field 1 of current line as an integer
    int a = f.getFieldAsInt(1);

    // retrieve field 2 as a float
    float b = f.getFieldAsFloat(2);

    // retrieve field 3 as a double
    double c = f.getFieldAsDouble(3);

    // retrieve field 4 as a float
    std::string d = f.getFieldAsString(4);

    // Check that input is o.k.
    if (f.inputFailed()) break;
  }
}
```

Simply link your application to the FileReader library to use it.

