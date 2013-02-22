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
This is the development version for Day 2 of the PP6 Course.

Installation
============
Prerequisites
-------------
- Unix operating system (Windows OS should work, but is not tested)
- C++98/11 compiler (`g++`/`clang++` tested)

Building pp6calculator
----------------------
Simply run the compiler on the `pp6calculator.cpp` and `PP6Math.cpp` 
files to output an executable. For example, using the GNU compiler:

```
$ g++ -W -Wall PP6Math.cpp pp6calculator.cpp -o pp6calculator
```

You may then run the resulting `pp6calculator` executable. Compilation
should succeed without warnings or errors.

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

