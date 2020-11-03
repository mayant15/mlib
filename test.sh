#!/bin/bash

cd tests
for file in $(ls *.cpp)
do
    g++ $file -o file-test
    ./file-test
done
