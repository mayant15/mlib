cmake_minimum_required (VERSION 3.13)
project(mmcontainers)
set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    tests/doctest.cpp
    
    tests/graph.cpp
    tests/lock.cpp
    tests/queue.cpp
    tests/stack.cpp
    tests/vector.cpp
)

add_executable(tests ${SOURCES})
target_include_directories(tests PRIVATE include)