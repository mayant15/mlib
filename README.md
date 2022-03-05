# mlib

![CI](https://github.com/mayant15/mlib/workflows/CI/badge.svg?branch=main)

Custom implementation of common data structures, types and utilities. All the things that I need to use everywhere.

Requires C++17.

## Usage

All containers are in `include/mm/**` and are header-only. Simply include the file and you're good to go. For example
```
#include <mm/vector.h>

int main(void)
{
    mm::vector<int> vec = {1, 2, 3, 4};
    vec[2] = 10;
}
```

## Tests

This library uses [doctest](https://github.com/onqtam/doctest/) for unit testing. Every container has a corresponding `<container>.cpp` file in `tests/**` with all test cases.
Compile the tests with CMake (`test.sh` does that).
