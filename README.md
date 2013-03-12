pp6calculator - A simple command line calculator
================================================
This is the README for the pp6calculator project, part of the MPAGS PP6
course on software development with C++.

Authors
-------
- Ben Morgan

License
-------
pp6calculator is distributed under the terms of the Boost Software License.

News
----
- 12/03/2013 : Day 4 Exercise Solutions Added
- 11/03/2013 : Day 3 Homework Solution Added
- 11/03/2013 : Day 3 Exercise Solutions Added
- 02/03/2013 : Solution of Day 2 Homework Implemented

Installation
============
Prerequisites
-------------
- Unix operating system (Windows OS should work, but is not tested)
- C++98/11 compiler (`g++`/`clang++` tested)
- [CMake](http://www.cmake.org) build tool, version 2.8 or higher

Building pp6calculator
----------------------
We recommend the following sequence of steps to build `pp6calculator` using
CMake and UNIX Makefiles:

1. Create a build directory parallel to the directory holding this README,
e.g.

        $ ls
        pp6calculator.git
        $ mkdir pp6calculator.build

2. Change into the build directory and run `cmake`, pointing it to the source
directory (i.e., the directory holding this README:

        $ cd pp6calculator.build
        $ cmake ../pp6calculator.git
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
        -- Build files have been written to: /Users/pp6/pp6calculator.build
        $

    The above output is for Mac OS X 10.6.8, so will vary slightly on other 
    systems. However, you should see the last three lines, which indicate
    a successful configuration.

3. Run `make` using the freshly generated Makefile:

        $ make
        Scanning dependencies of target pp6calculator
        [ 50%] Building CXX object CMakeFiles/pp6calculator.dir/pp6calculator.cpp.o
        [100%] Building CXX object CMakeFiles/pp6calculator.dir/PP6Lib/PP6Math.cpp.o
        Linking CXX executable pp6calculator
        [100%] Built target pp6calculator
        $
        
    The build should complete without warning or error.
    
4. You can simply run `pp6calculator` direct from the build directory

        $ ./pp6calculator

    At present, pp6calculator does not support installation.

Working With Git
================
Writing Good Commit Messages
----------------------------
Capitalized, short (50 chars or less) summary

More detailed explanatory text, if necessary.  Wrap it to about 72
characters or so.  In some contexts, the first line is treated as the
subject of an email and the rest of the text as the body.  The blank
line separating the summary from the body is critical (unless you omit
the body entirely); tools like rebase can get confused if you run the
two together.

Write your commit message in the imperative: "Fix bug" and not "Fixed bug"
or "Fixes bug."  This convention matches up with commit messages generated
by commands like git merge and git revert.

Further paragraphs come after blank lines.

- Bullet points are okay, too

- Typically a hyphen or asterisk is used for the bullet, preceded by a
  single space, with blank lines in between, but conventions vary here

- Use a hanging indent



References
==========
- [MPAGS PP6 Course Page](http://www2.warwick.ac.uk/fac/sci/physics/research/epp/resources/teaching/software_development_2012)
- [Git SCM](http://git-scm.com)

