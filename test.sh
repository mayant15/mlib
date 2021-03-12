#!/usr/bin/env bash

mkdir build
cd build
cmake ..
cmake --build .
./tests

# cd tests
# for file in $(ls *.cpp)
# do
#     g++ $file -o file-test
#     ./file-test
# done
