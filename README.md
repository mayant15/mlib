# mmcontainers

Custom implementation of common data structures

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

This library uses [doctest](https://github.com/onqtam/doctest/) for unit testing. Every container has a corresponding `<container>.cpp` file in `tests/**` with all test cases. Simply compile and run the source file
```
g++ vector.cpp -o vector
./vector
```
