#include "../doctest.h"
#include <mm/concurrent/set.h>

TEST_CASE("Test the concurrent set class")
{
    mm::concurrent::set<int> set;
    REQUIRE(set.size() == 0);

    SUBCASE("Test set::add()")
    {
        set.add(1);
        CHECK(set.size() == 1);

        set.add(2);
        set.add(3);
        CHECK(set.size() == 3);
    }

    SUBCASE("Test set::contains()")
    {
        set.add(1);
        set.add(2);
        CHECK(set.contains(1));
        CHECK(set.contains(2));
    }

    SUBCASE("Test set::remove()")
    {
        set.add(1);
        set.add(2);
        CHECK(set.size() == 2);

        set.remove(2);
        CHECK(set.size() == 1);
        CHECK(!set.contains(2));

        set.remove(1);
        CHECK(set.size() == 0);
        CHECK(!set.contains(1));
    }
}
