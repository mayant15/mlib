# mmcontainers

![CI](https://github.com/mayant15/mmcontainers/workflows/CI/badge.svg?branch=master)

Custom implementation of common data structures.

**NOTE:** C++17 features are used in this library, so compile with appropriate flags.

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
