#include "../doctest.h"
#include <mm/concurrent/set.h>

TEST_CASE("Test the concurrent set class")
{
    mm::concurrent::lazy_set<int> set;
    REQUIRE(set.size() == 0);

    SUBCASE("Test set::add()")
    {
        CHECK(set.add(1));
        CHECK(set.size() == 1);
        CHECK_FALSE(set.add(1));

        CHECK(set.add(2));
        CHECK(set.add(3));
        CHECK(set.size() == 3);
    }

    SUBCASE("Test set::contains()")
    {
        set.add(1);
        set.add(2);
        CHECK(set.contains(1));
        CHECK(set.contains(2));
        CHECK_FALSE(set.contains(3));
    }

    SUBCASE("Test set::remove()")
    {
        set.add(1);
        set.add(2);

        CHECK(set.remove(2));
        CHECK(set.size() == 1);
        CHECK(!set.contains(2));
        CHECK_FALSE(set.remove(2));

        CHECK(set.remove(1));
        CHECK(set.size() == 0);
        CHECK(!set.contains(1));
        CHECK_FALSE(set.remove(1));
    }
}
