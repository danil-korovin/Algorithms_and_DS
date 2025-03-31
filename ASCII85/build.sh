#!/bin/bash
set -e


CXXFLAGS="-std=c++14 -Wall -Wextra -pedantic"
LDFLAGS="-lgtest -lgtest_main -pthread"
MAIN_EXE="ascii85"
TEST_EXE="ascii85_tests"
SOURCE="ascii85.cpp main.cpp"
TEST_SOURCE="ascii85.cpp test.cpp"

g++ $CXXFLAGS -o $MAIN_EXE $SOURCE
g++ $CXXFLAGS -o $TEST_EXE $TEST_SOURCE $LDFLAGS

