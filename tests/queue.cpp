#include "doctest.h"
#include <mm/queue.h>

TEST_CASE("Test the queue class")
{
    //
}

TEST_CASE("Test the priority queue class")
{
    // TODO
    CHECK(true);
//    mm::priority_queue<int> pq(std::less<int>(), {3, 8, 4}); // NOLINT(modernize-use-transparent-functors)
//    REQUIRE(pq.size() == 3);
//    REQUIRE_FALSE(pq.empty());
//
//    SUBCASE("Test priority_queue::top()")
//    {
//        CHECK(pq.top() == 8);
//    }
//
//    SUBCASE("Test priority_queue::push()")
//    {
//        pq.push(11);
//        CHECK(pq.size() == 4);
//        CHECK(pq.top() == 11);
//    }
//
//    SUBCASE("Test priority_queue::emplace()")
//    {
//        pq.emplace(11);
//        CHECK(pq.size() == 4);
//        CHECK(pq.top() == 11);
//    }
//
//    SUBCASE("Test priority_queue::pop()")
//    {
//        pq.pop();
//        CHECK(pq.size() == 2);
//        CHECK(pq.top() == 4);
//    }
}
