#include "../doctest.h"
#include <mm/concurrent/set.h>
#include <thread>

TEST_CASE("Test the concurrent set class")
{
    mm::concurrent::lazy_set<int> set;
    REQUIRE(set.size() == 0);

    SUBCASE("Test set::add()")
    {
        CHECK(set.add(1));
        CHECK(set.size() == 1);
        CHECK_FALSE(set.add(1));

        bool other_thread;
        std::thread t1 ([&](){
            other_thread = set.add(3);
        });

        bool this_thread = set.add(2);

        t1.join();

        CHECK(this_thread);
        CHECK(other_thread);
        CHECK(set.size() == 3);
    }

    SUBCASE("Test set::contains()")
    {
        std::thread t1 ([&](){
            set.add(1);
        });

        std::thread t2 ([&](){
            set.add(2);
        });

        t1.join();
        t2.join();

        CHECK(set.contains(1));
        CHECK(set.contains(2));
        CHECK_FALSE(set.contains(3));
    }

    SUBCASE("Test set::remove()")
    {
        set.add(1);
        set.add(2);

        bool out1;
        std::thread t1 ([&](){
            out1 = set.remove(1);
        });

        bool out2;
        std::thread t2 ([&](){
            out2 = set.remove(2);
        });

        t1.join();
        t2.join();

        CHECK(out1);
        CHECK(out2);

        CHECK(set.size() == 0);

        CHECK(!set.contains(2));
        CHECK(!set.contains(1));

        CHECK_FALSE(set.remove(2));
        CHECK_FALSE(set.remove(1));
    }
}
