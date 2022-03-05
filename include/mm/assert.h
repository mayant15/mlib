#pragma once

#include <cassert>

#ifndef NDEBUG

#include <iostream>

#define DUMP(X) std::cout << X << std::endl;

#else

#define DUMP(X)

#endif