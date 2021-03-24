#include "../doctest.h"
#include <mm/math/random.h>

TEST_CASE("Testing the uniform_generator class")
{
    mm::uniform_generator rng;

    auto a = rng.next();
    CHECK(a >= 0);
    CHECK(a <= 1);

    auto b = rng.next();
    CHECK(b >= 0);
    CHECK(b <= 1);
}
